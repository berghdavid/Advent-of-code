#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

int submit(char* ans, char* day, char* level) {
	const char *session_token = getenv("AOC_SESSION");

	if (!session_token) {
		fprintf(stderr, "Error: AOC_SESSION environment variable is not set.\n");
		return 1;
	}

	char url[256];
	snprintf(url, sizeof(url), "https://adventofcode.com/2024/day/%s/answer", day);

	char post_data[256];
	snprintf(post_data, sizeof(post_data), "level=%s&answer=%s", level, ans);

	CURL *curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "Error: Unable to initialize cURL.\n");
		return 1;
	}

	// Create the header with the session cookie
	char cookie_header[256];
	snprintf(cookie_header, sizeof(cookie_header), "Cookie: session=%s", session_token);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(
		headers,
		"Content-Type: application/x-www-form-urlencoded"
	);
	headers = curl_slist_append(headers, cookie_header);

	// Set cURL options
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

	// Send the request and capture the response
	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		fprintf(
			stderr,
			"Error: cURL request failed: %s\n",
			curl_easy_strerror(res)
		);
	} else {
		printf("Answer submitted successfully!\n");
	}

	// Clean up
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	return res == CURLE_OK ? 0 : 1;
}

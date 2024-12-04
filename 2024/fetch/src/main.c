#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Callback function to write response data into a buffer
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
	size_t total_size = size * nmemb;
	FILE *output = (FILE *)userdata;
	fwrite(ptr, size, nmemb, output);
	return total_size;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Pass the day as an argument!\n");
		return 1;
	}
	if ((sizeof(argv[1]) / 4) > 2) {
		printf("Input day should only have 2 symbols, got %ld\n", sizeof(argv[1]));
		return 1;
	}

	// Replace this with your session token from the Advent of Code site
	const char *session_token = getenv("AOC_SESSION");
	if (!session_token) {
		fprintf(stderr, "Error: AOC_SESSION environment variable is not set.\n");
		return 1;
	}

	// Day and year to fetch input for
	int year = 2024;

	char url[256];
	snprintf(url, sizeof(url), "https://adventofcode.com/%d/day/%s/input", year, argv[1]);

	CURL *curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "Error: Unable to initialize cURL.\n");
		return 1;
	}

	// Create the header with the session cookie
	char cookie_header[256];
	snprintf(cookie_header, sizeof(cookie_header), "Cookie: session=%s", session_token);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, cookie_header);

	// Set cURL options
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

	// Output file for input data
	char filename[256];
	snprintf(filename, sizeof(filename), "../%s/data/data.in", argv[1]);
	FILE *output = fopen(filename, "wb");
	if (!output) {
		fprintf(stderr, "Error: Unable to open output file.\n");
		curl_easy_cleanup(curl);
		return 1;
	}
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);

	// Perform the request
	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		fprintf(stderr, "Error: cURL request failed: %s\n", curl_easy_strerror(res));
	} else {
		printf("Input data saved to %s\n", filename);
	}

	// Clean up
	fclose(output);
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	return res == CURLE_OK ? 0 : 1;
}

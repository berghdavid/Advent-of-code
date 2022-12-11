#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "utils.h"

/**
 * @brief Read the next positive integer.
 * 
 * @return Returns -1 on EOF and 0 if input is not a digit. Otherwise returns
 * any positive integer.
 */
int next_int()
{
        int     x;
        int     c;

	x = 0;

        if((c = getchar()) == EOF) {
                return -1;
        }
        while (isdigit(c)) {
                x = 10 * x + c - '0';
                c = getchar();
        }

        return x;
}

/**
 * @brief Run the solve() method of a suite. Measures execution time depending
 * on if the flag "time" is passed in the makefile.
 */
int main(int argc, char* argv[])
{
	char		ans[100];
	clock_t		start;
	clock_t		end;
	double		elapsed_ms;

	if (argc == 0) {
		return 0;
	}

	if (argc > 1 && strcmp(argv[1], "time") == 0) {
		start = clock();
		solve(ans);
		end = clock();

		elapsed_ms = (end - start) * 1000.0 / CLOCKS_PER_SEC;
		
		printf("%s execution time: %.3f (ms)\n", argv[0], elapsed_ms);
	} else {
		solve(ans);
	}

	printf("%s ans: %s\n", argv[0], ans);

	return 0;
}

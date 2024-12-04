#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

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

#include <stdio.h>
#include <ctype.h>
#include "utils.h"

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

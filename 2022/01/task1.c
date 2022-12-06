#include <stdio.h>
#include "../common/utils.h"

void solve(char* ans)
{
        int     max;
        int     sum;
        int     temp;

        max = sum = 0;
        while (1) {
                temp = next_int();
                if (temp == -1) {
                        if (sum > max) {
                                max = sum;
                                sum = 0;
                        }
                        break;
                }
                if (temp == 0) {
                        if (sum > max) {
                                max = sum;
                        }
                        sum = 0;
                } else {
                        sum += temp;
                }
        }

	sprintf(ans, "%d", max);
}

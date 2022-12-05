#include <stdio.h>
#include "../common/utils.h"

int main(int argc, char *argv[])
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

        printf("Task 1 ans: %d\n", max);

        return 0;
}

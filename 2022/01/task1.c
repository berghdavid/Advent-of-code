#include <stdio.h>
#include <sys/time.h>
#include <string.h>
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

int main(int argc, char* argv[])
{
	char		ans[100];
	struct timeval	begin, end;
	long		seconds;
	long		microseconds;
	double		elapsed_ms;

	if (argc == 0) {
		return 0;
	}

	if (argc > 1 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&begin, 0);
		solve(ans);
		gettimeofday(&end, 0);

		seconds = end.tv_sec - begin.tv_sec;
		microseconds = end.tv_usec - begin.tv_usec;
		elapsed_ms = seconds*1e3 + microseconds*1e-3;
		printf("%s execution time: %.3f (ms)\n", argv[0], elapsed_ms);
	} else {
		solve(ans);
	}

	printf("%s ans: %s\n", argv[0], ans);

	return 0;
}

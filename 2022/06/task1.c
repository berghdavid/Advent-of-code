#include <stdio.h>
#include <sys/time.h>
#include <string.h>

void solve(char* ans)
{
	int	length;
	char	c;
	char	c1;
	char	c2;
	char	c3;

	c3 = getchar();
	c2 = getchar();
	c1 = getchar();
	length = 4;
	while ((c = getchar()) != EOF) {
		if (c != c1 && c != c2 && c != c3 &&
		c1 != c2 && c1 != c3 && c2 != c3) {
			break;
		}
		c3 = c2;
		c2 = c1;
		c1 = c;
		length++;
	}

	sprintf(ans, "%d", length);
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

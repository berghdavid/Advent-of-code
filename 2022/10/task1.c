#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int next_signed_int()
{
        int	x;
        int     c;
	int	neg;

	x = 0;
	neg = 0;
        if((c = getchar()) == '-') {
		neg = 1;
		c = getchar();
        }
	while (isdigit(c)) {
		x = 10 * x + c - '0';
		c = getchar();
	}

	if (neg == 1) {
		x *= -1;
	}

        return x;
}

int tot_strength()
{
	int	x;
	int	buf;
	int	tot_str;
	int	cycle;
	int	i;

	tot_str = 0;
	x = 1;
	cycle = 0;
	buf = 0;

	while (cycle < 222) {
		cycle++;

		if (cycle % 40 == 20) {
			tot_str += cycle * x;
		}

		if (buf != 0) {
			x += buf;
			buf = 0;
		} else if (getchar() == 'a') {
			for (i = 0; i < 4; i++) {
				getchar();
			}
			buf = next_signed_int();
		} else {
			for (i = 0; i < 4; i++) {
				getchar();
			}
		}
	}

	return tot_str;
}

void solve(char* ans)
{
	int	sol;

	sol = tot_strength();

	sprintf(ans, "%d", sol);
}

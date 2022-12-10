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

void print_text(char* text, int len)
{
	int	i;

	for (i = 0; i < len; i++) {
		printf("%c", text[i]);
		if (i % 40 == 39) {
			printf("\n");
		}
	}
}

int tot_strength()
{
	int	x;
	int	buf;
	int	cycle;
	int	i;
	char*	text;
	int	len;

	len = 240;
	text = malloc((len + 1) * sizeof(char));
	text[len] = '\0';

	x = 0;
	cycle = 0;
	buf = 0;

	while (cycle < 240) {
		if (x <= cycle % 40 && cycle % 40 <= x + 2) {
			text[cycle] = '#';
		} else {
			text[cycle] = '.';
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
		cycle++;
	}

	print_text(text, len);
	free(text);

	return 0;
}

void solve(char* ans)
{
	int	sol;

	sol = tot_strength();

	sprintf(ans, "%d", sol);
}

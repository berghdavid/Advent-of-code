#include <stdio.h>

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

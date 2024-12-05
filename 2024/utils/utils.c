#include <stdio.h>
#include <ctype.h>

/**
 * @brief Read the next positive integer.
 * 
 * @return Returns -1 on EOF and 0 if input is not a digit. Otherwise returns
 * any positive integer.
 */
int next_positive_int()
{
	int	x;
	int	c;

	c = getchar();
	while (!isdigit(c)) {
		if (c == EOF) {
			return -1;
		}
		c = getchar();
	}

	x = 0;
	while (isdigit(c)) {
		x = 10 * x + c - '0';
		c = getchar();
	}

	return x;
}

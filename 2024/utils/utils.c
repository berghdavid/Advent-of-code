#include <stdio.h>
#include <ctype.h>

typedef struct Pack Pack;

struct Pack {
	int	val;
	char	end;
};

/**
 * @brief Read the next positive integer.
 * 
 * @return Returns -1 on EOF. Otherwise returns any positive integer.
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

/**
 * @brief Read the next positive integer.
 * 
 * @return Returns -1 on EOF and -2 if newline. Otherwise returns
 * any positive integer.
 */
int next_positive_int2()
{
	int	x;
	int	c;

	c = getchar();
	while (!isdigit(c)) {
		if (c == EOF) {
			return -1;
		}
		if (c == '\n') {
			return -2;
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

/**
 * @brief Read the next positive integer.
 * 
 * @return Returns -1 on EOF and -2 if newline. Otherwise returns
 * any positive integer.
 */
Pack* next_positive_int3()
{
	Pack*	p;

	p = malloc(sizeof(Pack));
	p->val = -1;
	p->end = getchar();

	while (!isdigit(p->end)) {
		if (p->end == EOF) {
			return p;
		}
		if (p->end == '\n') {
			return p;
		}
		p->end = getchar();
	}

	p->val = 0;
	while (isdigit(p->end)) {
		p->val = 10 * p->val + p->end - '0';
		p->end = getchar();
	}
	return p;
}

char read_to_end()
{
	char	c;

	c = '\n';
	while ((c = getchar()) != EOF && c != '\n') {
		continue;
	}
	return c;
}

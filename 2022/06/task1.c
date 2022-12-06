#include <stdio.h>

int count_marker_length()
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
		if (c != c1 && c != c2 && c != c3 && c1 != c2 && c1 != c3 && c2 != c3) {
			return length;
		}
		c3 = c2;
		c2 = c1;
		c1 = c;
		length++;
	}

	return length;
}

int main(void)
{
	int	ans;

	ans = count_marker_length();

	printf("Task 1 ans: %d\n", ans);

	return 0;
}

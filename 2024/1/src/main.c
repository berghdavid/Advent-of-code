#include <stdio.h>
#include "../../utils/utils.c"

int main()
{
	int	prev;
	int	curr;
	int	counter;
	int	sum;

	counter = 0;
	prev = 0;
	while((curr = next_positive_int()) >= 0)
	{
		if (counter % 2 == 0) {
			prev = curr;
		} else {
			if (prev < curr) {
				sum += curr - prev;
			} else {
				sum += prev - sum;
			}
		}
		counter++;
	}

	printf("Ans: %d\n", sum);
}

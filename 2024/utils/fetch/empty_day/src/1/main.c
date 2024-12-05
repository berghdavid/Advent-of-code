#include <stdio.h>
#include <stdlib.h>
#include "../../../utils/utils.c"

int main(int argc, char* argv[])
{
	char	ans[2048];
	int	curr;
	int	counter;
	int	sum;

	sum = 0;
	counter = 0;
	while((curr = next_positive_int()) >= 0) {
		counter++;
	}

	printf("Ans: %d\n", sum);
	sprintf(ans, "%d", sum);

	if (argc == 3) {
		// Post answer to AoC
		submit(ans, argv[1], argv[2]);
	}
}

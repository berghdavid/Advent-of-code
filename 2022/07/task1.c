#include <stdio.h>
#include <ctype.h>

int get_file_size()
{
        int     x;
        int     c;

	x = 0;

        if((c = getchar()) == '$') {
                return -2;
        } else if() {
		
	}
        while (isdigit(c)) {
                x = 10 * x + c - '0';
                c = getchar();
        }

        return x;
}

int next_ls()
{
	char	c;
	int	size;

	while ((c = getchar()) != EOF) {
		if (c != '$') {
			continue;
		}

		/* Skip space */
		getchar();

		if (getchar() != 'l') {
			continue;
		}
		
		/* Skip s\n */
		getchar();
		getchar();

		
	}
}

void solve(char* ans)
{
	int	size;

	size = 0;

	sprintf(ans, "%d", size);
}

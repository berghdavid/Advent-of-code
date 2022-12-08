#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int MAX_STRING = 11;

typedef struct Dir Dir;

struct Dir {
	int	subs;
	int	size;
	char*	name;
	Dir*	par;
	Dir*	sub;
};

void finish_row()
{
	char	c;

	c = getchar();
	while (c != '\n') {
		c = getchar();
	}
}

void print_subdirs(Dir* d, int depth)
{
	int	i;

	for (i = 0; i < depth; i++) {
		printf("  ");
	}
	printf("- %s (%d)\n", d->name, d->size);

	for (i = 0; i < d->subs; i++) {
		print_subdirs(&d->sub[i], depth + 1);
	}
}

Dir* malloc_dir(char* name, Dir* parent, int subfolders, int size)
{
	int	i;
	Dir*	d;

	d = malloc(sizeof(Dir));
	d->name = name;
	d->par = parent;
	d->subs = subfolders;
	d->size = size;
	if (subfolders == 0) {
		d->sub = NULL;
	} else {
		d->sub = malloc(subfolders * sizeof(Dir));
		for (i = 0; i < subfolders; i++) {
			d->sub[i].par = d;
			d->sub[i].sub = NULL;
			d->sub[i].subs = 0;
			d->sub[i].size = 0;
		}
	}

	return d;
}

void init_subdirs(Dir* d, char** names, int subfolders)
{
	int	i;

	d->subs = subfolders;
	if (subfolders == 0) {
		d->sub = NULL;
	} else {
		d->sub = malloc(subfolders * sizeof(Dir));
		for (i = 0; i < subfolders; i++) {
			init_empty_dir(&d->sub[i], d, names[i]);
		}
	}
}

void init_empty_dir(Dir* d, Dir* parent, char* name)
{
	d->name = name;
	d->size = 0;
	d->subs = 0;
	d->sub = NULL;
	d->par = parent;
}

void clean_subdir(Dir* d)
{
	int	i;

	free(d->name);

	if (d->subs == 0) {
		return;
	}

	for (i = 0; i < d->subs; i++) {
		clean_subdir(&d->sub[i]);
	}

	free(d->sub);
}

char* read_string()
{
	char*	str;
	char	c;
	int	i;

	str = malloc(MAX_STRING * sizeof(char));
	str[MAX_STRING - 1] = '\0';

	i = 0;
	while ((c = getchar()) != '\n') {
		str[i++] = c;
	}

	return str;
}

Dir* find_subdir(Dir* curr, char* name)
{
	int	i;

	for (i = 0; i < curr->subs; i++) {
		if (strcmp(curr->sub[i].name, name) == 0) {
			return &curr->sub[i];
		}
	}
	return curr;
}

void read_to_dir(Dir* d)
{
	int	nbr;
	int	subs;
	char	c;
	char**	strings;
	Dir*	curr;

	strings = malloc(10 * sizeof(char*));
	curr = d;
	subs = 0;
	nbr = 0;

	while ((c = getchar()) != EOF) {
		if (isdigit(c)) {
			nbr = 10 * nbr + c - '0';
		} else if (nbr > 0) {
			printf("%s: %d -> %d = %d\n",
				curr->name, nbr, curr->size, nbr + curr->size);
			curr->size += nbr;
			nbr = 0;
			finish_row();
		} else if (c == 'd') {
			/* Current row is "dir xxxxx" */
			getchar();
			getchar();
			getchar();
			getchar();
			strings[subs++] = read_string();
			subs++;
		} else if (c == '$') {
			/* There will always be a "$ cd " here */
			init_subdirs(curr, strings, subs);
			subs = 0;

			getchar();
			getchar();
			getchar();

			c = getchar();
			if (c == '.') {
				curr = curr->par;
				finish_row();
			} else {
				strings[0] = read_string();
				curr = find_subdir(curr, strings[0]);
				free(strings[0]);
			}
		}
	}
	free(strings);
}

Dir* build_system()
{
	Dir*	root;
	char*	name;

	name = malloc(2 * sizeof(char));
	name[0] = '/';
	name[1] = '\0';

	root = malloc(sizeof(Dir));
	root->name = name;
	root->par = NULL;
	root->size = 0;

	finish_row();
	finish_row();
	read_to_dir(root);

	return root;
}

void solve(char* ans)
{
	int	size;
	Dir*	root;

	size = 0;
	root = build_system();

	/* TODO: Read system */

	sprintf(ans, "%d", size);

	clean_subdir(root);
	free(root);
}

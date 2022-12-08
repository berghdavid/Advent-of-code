#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Dir Dir;

struct Dir {
	int	subs;
	int	size;
	char*	name;
	Dir*	par;
	Dir*	sub;
};

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

void init_dir(Dir* d, char* name, int subfolders, int size)
{
	int	i;

	d->name = name;
	d->size = size;
	d->subs = subfolders;
	if (subfolders == 0) {
		d->sub = NULL;
	} else {
		d->sub = malloc(subfolders * sizeof(Dir));
		for (i = 0; i < subfolders; i++) {
			d->sub[i].par = d;
			init_dir(&d->sub[i], NULL, 0, 0);
		}
	}
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

void read_to_dir(Dir* d)
{

}

Dir* build_system()
{
	Dir*	root;
	char*	name;

	name = malloc(2 * sizeof(char));
	name[0] = '/';
	name[1] = '\0';

	root = malloc(sizeof(Dir));

	init_dir(root, name, 3, 100);

	return root;
}

void solve(char* ans)
{
	int	size;
	Dir*	root;

	size = 0;
	root = build_system();

	/*
	while ((c = getchar()) != EOF) {
		if (isdigit(c)) {
			nbr = 10 * nbr + c - '0';
		} else if (nbr > 0) {
			//printf("Adding: %d -> %d = %d\n", nbr, size, nbr+size);
			size += nbr;
			nbr = 0;
		}
	}*/

	sprintf(ans, "%d", size);

	clean_subdir(root);
	free(root);
}

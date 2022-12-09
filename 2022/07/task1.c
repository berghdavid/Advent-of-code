#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int MAX_STRING = 11;

typedef struct Dir Dir;

struct Dir {
	char*	name;	/* Name of directory			*/
	int	size;	/* Total size of files in directory	*/
	Dir*	par;	/* Parent directory			*/
	Dir*	next;	/* Directory with same parent directory	*/
	Dir*	sub;	/* Subdirectory				*/
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

	if (d->sub != NULL) {
		print_subdirs(d->sub, depth + 1);
	}

	if (d->next != NULL) {
		print_subdirs(d->next, depth);
	}
}

Dir* init_dir()
{
	Dir*	d;

	d = malloc(sizeof(Dir));
	d->name = NULL;
	d->size = 0;
	d->par = NULL;
	d->next = NULL;
	d->sub = NULL;

	return d;
}

void clean_subdir(Dir* d)
{
	free(d->name);

	if (d->sub != NULL) {
		clean_subdir(d->sub);
	}

	if (d->next != NULL) {
		clean_subdir(d->next);
	}

	free(d);
}

char* read_string()
{
	char*	str;
	char	c;
	int	i;

	str = calloc(MAX_STRING, sizeof(char));
	str[MAX_STRING - 1] = '\0';

	i = 0;
	while ((c = getchar()) != '\n' && i < MAX_STRING - 1) {
		str[i] = c;
		i++;
	}

	return str;
}

void add_subdir(Dir* parent, Dir* sub)
{
	Dir*	d;

	//printf("Adding %s to directory %s\n", sub->name, parent->name);

	sub->par = parent;
	if (parent->sub == NULL) {
		parent->sub = sub;
		return;
	}
	d = parent->sub;
	while (d->next != NULL) {
		d = d->next;
	}
	d->next = sub;
}

Dir* find_subdir(Dir* sub, char* name)
{
	if (sub == NULL) {
		printf("ERROR: COULD NOT FIND SUBDIR: %s\n", name);
		return sub;
	} else if (strcmp(sub->name, name) == 0) {
		return sub;
	}
	return find_subdir(sub->next, name);
}

void read_to_dir(Dir* d)
{
	int	nbr;
	char	c;
	char*	str;
	Dir*	curr;
	Dir*	sub;

	curr = d;
	nbr = 0;

	while ((c = getchar()) != EOF) {
		if (isdigit(c)) {
			nbr = 10 * nbr + c - '0';
		} else if (nbr > 0) {
			//printf("Adding %d to %s\n", nbr, curr->name);
			curr->size += nbr;
			nbr = 0;
			finish_row();
		} else if (c == 'd') {
			/* Current row is "dir xxxxx" */
			getchar();
			getchar();
			getchar();

			sub = init_dir();
			sub->name = read_string();
			add_subdir(curr, sub);
		} else if (c == '$') {
			getchar();
			if (getchar() == 'l') {
				/* Skip "$ ls" */
				finish_row();
				continue;
			}

			getchar();
			getchar();
			str = read_string();
			if (str[0] == '.') {
				//printf("Entering %s\n", curr->par->name);
				curr = curr->par;
			} else {
				//printf("Entering %s\n", str);
				curr = find_subdir(curr->sub, str);
			}
			free(str);
		}
	}
}

Dir* build_system()
{
	Dir*	root;
	char*	name;

	name = malloc(2 * sizeof(char));
	name[0] = '/';
	name[1] = '\0';

	root = init_dir();
	root->name = name;

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
	//print_subdirs(root, 1);

	/* TODO: Read system */

	sprintf(ans, "%d", size);

	clean_subdir(root);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int MAX_STRING = 11;
const long MAX_FILE = 100000;

typedef struct Dir Dir;

struct Dir {
	char*	name;	/* Name of directory			*/
	long	size;	/* Total size of files in directory	*/
	Dir*	par;	/* Parent directory			*/
	Dir*	next;	/* Directory with same parent directory	*/
	Dir*	sub;	/* Subdirectory				*/
};

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
	printf("- %s (%ld)\n", d->name, d->size);

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

void add_subdir(Dir* parent, Dir* sub)
{
	Dir*	d;

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

void inc_dirsize(Dir* d, int size)
{
	d->size += size;
	if (d->par != NULL) {
		inc_dirsize(d->par, size);
	}
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
			inc_dirsize(curr, nbr);
			nbr = 0;
			finish_row();
		} else if (c == 'd') {
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
				curr = curr->par;
			} else {
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

int get_total_size(Dir* d)
{
	int	n;

	n = 0;
	if (d->size < MAX_FILE) {
		n += d->size;
	}

	if (d->sub != NULL) {
		n += get_total_size(d->sub);
	}
	
	if (d->next != NULL) {
		n += get_total_size(d->next);
	}
	return n;
}

void solve(char* ans)
{
	long	size;
	Dir*	root;

	root = build_system();

	size = get_total_size(root);

	sprintf(ans, "%ld", size);

	clean_subdir(root);
}

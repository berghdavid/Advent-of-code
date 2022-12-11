#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const int MONKEY_NBR = 8;

typedef struct Item Item;
typedef struct Monkey Monkey;

struct Item {
	int	worry;
	Item*	next;
};

struct Monkey {
	Item*	first;
	int	add_op;
	int	mul_op;
	int	mul_old;
	int	div;
	Monkey*	t_monkey;
	Monkey*	f_monkey;
	Monkey*	monkeys;
};

int nextint()
{
	int	x;
	int	c;

	x = 0;

	while (isdigit(c = getchar())) {
		x = 10 * x + c - '0';
	}

	return x;
}

void jump_chars(int nbr)
{
	int	i;

	for (i = 0; i < nbr; i++) {
		getchar();
	}
}

void finish_line()
{
	char	c;

	c = getchar();
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}

Monkey* init_monkeys()
{
	int	i;
	Monkey*	monkeys;
	Monkey* m;

	monkeys = malloc(MONKEY_NBR * sizeof(Monkey));
	for (i = 0; i < MONKEY_NBR; i++) {
		m = &monkeys[i];
		m->first = NULL;
		m->monkeys = monkeys;
		m->add_op = 0;
		m->mul_op = 1;
		m->mul_old = 1;
		m->div = 0;
		m->t_monkey = NULL;
		m->f_monkey = NULL;
	}
	return monkeys;
}

Item* init_item(int worry)
{
	Item*	item;

	item = malloc(sizeof(Item));
	item->worry = worry;
	item->next = NULL;
	return item;
}

void clean_item(Item* item)
{
	Item*	i;
	Item*	tmp;

	i = item;
	while (i != NULL) {
		tmp = i->next;
		free(i);
		i = tmp;
	}
}

void clean_monkeys(Monkey* monkeys)
{
	int	i;

	for (i = 0; i < MONKEY_NBR; i++) {
		clean_item(monkeys[i].first);
	}
	free(monkeys);
}

void push_item(Monkey* m, Item* item)
{
	Item*	i;

	if (m->first == NULL) {
		m->first = item;
		return;
	}

	i = m->first;
	while (i->next != NULL) {
		i = i->next;
	}
	i->next = item;
}

Item* pop_item(Monkey* m)
{
	Item*	i;

	if (m->first == NULL) {
		printf("ERROR: Popping empty item list.\n");
		return NULL;
	}
	i = m->first;
	m->first = i->next;
	i->next = NULL;
	return i;
}

void read_to_monkey(Monkey* m)
{
	int	nbr;
	char	c;
	Item*	i;

	/* Read monkey items */
	jump_chars(18);
	nbr = nextint();
	while (nbr != 0) {
		i = init_item(nbr);
		push_item(m, i);
	}

	/* Read operation */
	jump_chars(23);
	c = getchar();
	getchar();
	if (c == '+') {
		nbr = nextint();
		m->add_op = nbr;
	} else if ((nbr = nextint()) == 0) {
		m->mul_old = 2;
		finish_line();
	} else {
		m->mul_op = nbr;
	}

	/* Read test */
	jump_chars(21);
	nbr = nextint();
	m->div = nbr;

	/* Read true test monkey */
	jump_chars(29);
	nbr = nextint();
	m->t_monkey = &m->monkeys[nbr];

	/* Read false test monkey */
	jump_chars(29);
	nbr = nextint();
	m->f_monkey = &m->monkeys[nbr];
}

void read_to_monkeys(Monkey* monkeys)
{
	int	i;
	Monkey* m;

	for (i = 0; i < MONKEY_NBR; i++) {
		m = &monkeys[i];
		printf("Read monkey\n");
		read_to_monkey(m);
	}
}

void solve(char* ans)
{
	int	sol;
	Monkey*	monkeys;

	monkeys = init_monkeys();

	read_to_monkeys(monkeys);

	clean_monkeys(monkeys);
	sol = 0;

	sprintf(ans, "%d", sol);
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const int MONKEY_NBR = 8;

typedef struct Item Item;
typedef struct Monkey Monkey;

struct Item {
	long	worry;
	Item*	next;
};

struct Monkey {
	int	id;
	long	counter;
	Item*	first;
	int	add_op;
	int	mul_op;
	int	mul_old;
	long	div;
	long	rel;
	Monkey*	t_monkey;
	Monkey*	f_monkey;
	Monkey*	monkeys;
};

long power(long a, long b)
{
	if (b == 1) {
		return a;
	}
	return a * a;
}

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
		m->id = i;
		m->counter = 0;
		m->first = NULL;
		m->monkeys = monkeys;
		m->add_op = 0;
		m->mul_op = 1;
		m->mul_old = 1;
		m->div = 0;
		m->rel = 0;
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

	item->next = NULL;
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

	finish_line();

	/* Read monkey items */
	jump_chars(18);
	while ((nbr = nextint()) != 0) {
		i = init_item(nbr);
		push_item(m, i);
		if (getchar() == '\n') {
			break;
		}
	}

	/* Read operation */
	jump_chars(21);
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
	m->div = (long) nbr;

	/* Read true test monkey */
	jump_chars(29);
	nbr = nextint();
	m->t_monkey = &m->monkeys[nbr];

	/* Read false test monkey */
	jump_chars(30);
	nbr = nextint();
	m->f_monkey = &m->monkeys[nbr];
	finish_line();
}

void print_monkey(Monkey* m)
{
	Item*	item;

	printf("Monkey %d:\n", m->id);
	printf("  Inspected items: %ld\n", m->counter);
	printf("  Items: ");
	item = m->first;
	if (item != NULL) {
		printf("%ld", item->worry);
		while (item->next != NULL) {
			printf(", %ld", item->next->worry);
			item = item->next;
		}
	}
	printf("\n");
}

void print_monkeys(Monkey* monkeys)
{
	int	i;

	for (i = 0; i < MONKEY_NBR; i++) {
		print_monkey(&monkeys[i]);
	}
}

void read_to_monkeys(Monkey* monkeys)
{
	int	i;
	int	rel;
	Monkey* m;

	rel = 1;
	for (i = 0; i < MONKEY_NBR; i++) {
		m = &monkeys[i];
		read_to_monkey(m);
		rel *= m->div;
	}

	for (i = 0; i < MONKEY_NBR; i++) {
		m = &monkeys[i];
		m->rel = rel;
	}
}

void inspect_item(Monkey* m, Item* item)
{
	item->worry %= m->rel;
	item->worry = power(item->worry, m->mul_old) * m->mul_op + m->add_op;

	if (item->worry % m->div == 0) {
		push_item(m->t_monkey, item);
	} else {
		push_item(m->f_monkey, item);
	}
	m->counter++;
}

void simulate_monkey(Monkey* m)
{
	Item*	item;

	while ((item = pop_item(m)) != NULL) {
		inspect_item(m, item);
	}
}

void simulate_rounds(Monkey* monkeys, int rounds)
{
	int	i;
	int	j;

	for (i = 0; i < rounds; i++) {
		for (j = 0; j < MONKEY_NBR; j++) {
			simulate_monkey(&monkeys[j]);
		}
	}
}

long monkey_business(Monkey* monkeys)
{
	int	i;
	long	score;
	long	max_1;
	long	max_2;
	
	max_1 = 0;
	max_2 = 0;
	for (i = 0; i < MONKEY_NBR; i++) {
		score = monkeys[i].counter;
		if (score > max_1) {
			max_2 = max_1;
			max_1 = score;
		} else if (score > max_2) {
			max_2 = score;
		}
	}
	return max_1 * max_2;
}

void solve(char* ans)
{
	long	sol;
	Monkey*	monkeys;

	monkeys = init_monkeys();
	read_to_monkeys(monkeys);
	simulate_rounds(monkeys, 10000);
	sol = monkey_business(monkeys);

	clean_monkeys(monkeys);
	sprintf(ans, "%ld", sol);
}

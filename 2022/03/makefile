.PHONY: all valgrind

all: run_time clean
valgrind: valg clean

.PHONY: gcc
gcc: task1.c task2.c utils.c utils.h
	@gcc task1.c utils.c -o task1
	@gcc task2.c utils.c -o task2

.PHONY: run_time
FORMAT = '\t- Execution time: %E\n\t- Maximum resident set size (kb): %M'
run_time: gcc
	@time -f $(FORMAT) ./task1 < data1.in
	@time -f $(FORMAT) ./task2 < data2.in

.PHONY: gcc-debug
gcc-debug: task1.c task2.c utils.c utils.h
	@gcc task1.c utils.c -ggdb3 -o task1
	@gcc task2.c utils.c -ggdb3 -o task2

.PHONY: valg
valg: gcc-debug
	@valgrind --leak-check=full ./task1 < data1.in
	@valgrind --leak-check=full ./task2 < data2.in

.PHONY: clean
clean: gcc
	@rm task1 task2

.PHONY: all
all: gcc run clean

.PHONY: gcc
gcc: task1.c task2.c utils.c utils.h
	@gcc task1.c utils.c -o task1
	@gcc task2.c utils.c -o task2

.PHONY: run
FORMAT = '\t- Execution time: %E\n\t- Maximum resident set size (kb): %M'
run: gcc
	@time -f $(FORMAT) ./task1 < data1.in
	@time -f $(FORMAT) ./task2 < data2.in

.PHONY: clean
clean: gcc
	@rm task1 task2

.PHONY: all
all: gcc run clean

gcc: task1.c task2.c utils.c utils.h
	@gcc task1.c utils.c -o task1
	@gcc task2.c utils.c -o task2

.PHONY: run
run: gcc
	@./task1 < data1.in
	@./task2 < data2.in

.PHONY: clean
clean: gcc
	@rm task1 task2

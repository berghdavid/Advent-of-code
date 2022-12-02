.PHONY: run time valgrind

run: run_simple clean
time: run_time clean
valgrind: run_valg clean

.PHONY: gcc
gcc: task1.c task2.c utils.c utils.h
	@gcc task1.c utils.c -o task1
	@gcc task2.c utils.c -o task2

.PHONY: run_simple
run_simple: gcc
	@./task1 < data1.in
	@./task2 < data2.in

.PHONY: run_time
FORMAT = '\t- Execution time: %E'
run_time: gcc
	@time -f $(FORMAT) ./task1 < data1.in
	@time -f $(FORMAT) ./task2 < data2.in

.PHONY: gcc-debug
gcc-debug: task1.c task2.c utils.c utils.h
	@gcc task1.c utils.c -ggdb3 -o task1
	@gcc task2.c utils.c -ggdb3 -o task2

.PHONY: run_valg
run_valg: gcc-debug
	@valgrind --leak-check=full --track-origins=yes ./task1 < data1.in
	@valgrind --leak-check=full --track-origins=yes ./task2 < data2.in

.PHONY: clean
clean: gcc
	@rm task1 task2

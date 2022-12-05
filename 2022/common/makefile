.PHONY: run time valgrind

run: run_simple clean
time: run_time clean
valgrind: run_valg clean

.PHONY: gcc
gcc: task1.c task2.c ../common/utils.c ../common/utils.h
	@gcc task1.c ../common/utils.c -o task1
	@gcc task2.c ../common/utils.c -o task2

.PHONY: run_simple
run_simple: gcc
	@./task1 < data.in
	@./task2 < data.in

.PHONY: run_time
FORMAT = '\t- Execution time: %E'
run_time: gcc
	@time -f $(FORMAT) ./task1 < data.in
	@time -f $(FORMAT) ./task2 < data.in

.PHONY: gcc-debug
gcc-debug: task1.c task2.c ../common/utils.c ../common/utils.h
	@gcc task1.c ../common/utils.c -ggdb3 -Wall -o task1
	@gcc task2.c ../common/utils.c -ggdb3 -Wall -o task2

.PHONY: run_valg
run_valg: gcc-debug
	@valgrind --leak-check=full --track-origins=yes ./task1 < data.in
	@valgrind --leak-check=full --track-origins=yes ./task2 < data.in

.PHONY: clean
clean: gcc
	@rm task1 task2

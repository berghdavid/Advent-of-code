CC          = gcc
W_FLAGS     = -Wall -Wextra -Wpedantic -Werror
LDFLAGS     = -lm
OPT_FLAGS   = -O3
VG_FLAGS    = -O0 -g


C_FILES = $(wildcard src/*.c)

all: build

run: build
	@./bin/main

build: $(C_FILES)
	@$(CC) -o bin/main $(W_FLAGS) $(OPT_FLAGS) $(C_FILES) $(LDFLAGS)

debug_vg: build_vg # Run using Valgrind memcheck
	@valgrind --tool=memcheck --track-origins=yes ./bin/main_vg

build_vg: $(C_FILES)
	@$(CC) -o bin/main_vg $(VG_FLAGS) $(W_FLAGS) $(C_FILES) $(LDFLAGS)

clean: all
	@rm bin/*

CC          = gcc
LDFLAGS     = -lm -lcurl
OPT_FLAGS   = -O3
VG_FLAGS    = -O0 -g

C_1_FILES = $(wildcard src/1/*.c)
C_2_FILES = $(wildcard src/2/*.c)

all: build_1 build_2

1: build_1
	@./bin/1 < data/data.in

2: build_2
	@./bin/2 < data/data2.in

build_1: $(C_1_FILES)
	@$(CC) -o bin/1 $(W_FLAGS) $(OPT_FLAGS) $(C_1_FILES) $(LDFLAGS)

build_2: $(C_2_FILES)
	@$(CC) -o bin/2 $(W_FLAGS) $(OPT_FLAGS) $(C_2_FILES) $(LDFLAGS)

debug_1_vg: build_1_vg # Run using Valgrind memcheck
	@valgrind --tool=memcheck --track-origins=yes ./bin/1_vg < data/data.in

build_1_vg: $(C_1_FILES)
	@$(CC) -o bin/1_vg $(VG_FLAGS) $(W_FLAGS) $(C_1_FILES) $(LDFLAGS)

debug_2_vg: build_2_vg # Run using Valgrind memcheck
	@valgrind --tool=memcheck --track-origins=yes ./bin/2_vg < data/data.in

build_2_vg: $(C_2_FILES)
	@$(CC) -o bin/2_vg $(VG_FLAGS) $(W_FLAGS) $(C_2_FILES) $(LDFLAGS)

clean: all
	@rm bin/*

CC          = gcc
W_FLAGS     = -Wall -Wextra -Wpedantic -Werror
LDFLAGS     = -lcurl
OPT_FLAGS   = -O3
VG_FLAGS    = -O0 -g

C_FILES = $(wildcard src/*.c)

all: build

build: $(C_FILES)
	@$(CC) -o bin/main $(W_FLAGS) $(OPT_FLAGS) $(C_FILES) $(LDFLAGS)

build_vg: $(C_FILES)
	@$(CC) -o bin/main_vg $(VG_FLAGS) $(W_FLAGS) $(C_FILES) $(LDFLAGS)

clean: all
	@rm bin/*

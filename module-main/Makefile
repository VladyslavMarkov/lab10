CC = clang
LAB_OPTS = -I../module-library/src ../module-library/src/lib.c
C_OPTS = $(MAC_OPTS) -std=gnu11 -g -lm -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla $(LAB_OPTS)


clean:
	rm -rf ../dist

prep:
	 mkdir ../dist

compile: main.bin

main.bin: src/main.c
	$(CC) $(C_OPTS) $< -o ../dist/$@

all:clean prep compile 
	./dist/main.bin
check:
	clang-format --verbose -dry-run --Werror src/*
	clang-tidy src/*.c  -checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.rand
	rm -rf src/*.dump



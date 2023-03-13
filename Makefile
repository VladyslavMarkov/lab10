CC = clang
LAB_OPTS = -I./module-library/src module-library/src/lib.c 
LIB_H = -I./module-library/src
C_OPTS = $(MAC_OPTS) -std=gnu11 -g -lm -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla $(LAB_OPTS)
DOCG = doxygen
DOC = Doxyfile

compile_all: clean prep main.bin test.bin


clean:
	rm -rf ./dist
prep:
	mkdir ./dist
compile: clean prep main.bin

main.bin: module-main/src/main.c
	$(CC) $(C_OPTS) $< -o ./dist/$@
check:
	clang-format --verbose -dry-run --Werror src/*
	clang-tidy src/*.c  -checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.rand
	rm -rf src/*.dump




clean_doxy:
	rm -rf ./dist/html
	rm -rf ./dist/latex 
Doxygen:
	$(DOCG) $(DOC)
	
compile_doxy: clean_doxy Doxygen




compile_test: clean prep test.bin

test.bin:module-library/test/test.c
	 $(CC) $(C_OPTS) $< -fprofile-instr-generate -fcoverage-mapping -lsubunit  -o ./dist/$@ -lcheck 
test: prep compile_2
		LLVM_PROFILE_FILE="dist/test.profraw" ./dist/test.bin
		llvm-profdata merge -sparse dist/test.profraw -o dist/test.profdata
		llvm-cov report dist/test.bin -instr-profile=dist/test.profdata src/*.c
		llvm-cov show dist/test.bin -instr-profile=dist/test.profdata src/*.c --format html > dist/coverage.html
	
	
	
dynamic_lib.o:module-library/src/lib.c
	$(CC) -c -fPIC $< -o ./dist/$@

dynamic_lib.h.gch:module-library/src/lib.h
	$(CC) -c -fPIC $< -o ./dist/$@ 

dynamic_main.o:module-main/src/main.c
	$(CC) $(LIB_H) -c $< -o ./dist/$@

dynamic_lib_lab10:
	$(CC) -shared dist/dynamic_lib.o dist/dynamic_lib.h.gch -o lib_lab10.so  

compile_dynamic_lib:clean prep dynamic_lib.o dynamic_lib.h.gch dynamic_main.o dynamic_lib_lab10

clean_dynamic_OBJ:
	rm -rf ./dist/dynamic_main.o
	rm -rf ./dist/dynamic_lib.h.gch
	rm -rf ./dist/dynamic_lib.o

dynamic_main.bin:	
	$(CC) -o ./dist/dynamic_main.bin dist/dynamic_main.o -L. -l_lab10 -rpath -Wl

dynamic_test.bin:
	$(CC) $(C_OPTS) module-library/test/test.c -L. -l_lab10 -rpath -Wl $< -fprofile-instr-generate -fcoverage-mapping -lsubunit -o ./dist/dynamic_test.bin -lcheck

	



static_lib.o:module-library/src/lib.c
	$(CC) -c $< -o ./dist/$@
static_lib.h.o:module-library/src/lib.h
	$(CC) -c $< -o ./dist/$@ 
static_main.o:module-main/src/main.c
	$(CC) $(LIB_H) -c $< -o ./dist/$@
static_lib_lab10:
	ar rc lib_lab10.a dist/static_lib.o dist/static_lib.h.o
	ranlib lib_lab10.a

static_main.bin:	
	$(CC) dist/static_main.o -L. -l_lab10 $< -o ./dist/satic_main.bin
	
static_test.bin:
	$(CC) $(C_OPTS) module-library/test/test.c -L. -l_lab10 $< -fprofile-instr-generate -fcoverage-mapping -lsubunit -o ./dist/static_test.bin -lcheck

clean_static_OBJ:
	rm -rf ./dist/static_lib.o
	rm -rf ./dist/static_lib.h.o
	rm -rf ./dist/static_main.o

compile_static_lib: clean prep static_lib.o static_lib.h.o static_main.o static_lib_lab10 
	

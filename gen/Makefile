CC=g++
C11= -std=c++0x
FLAGSBASE= -O3 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wshadow -Wwrite-strings -Wsign-compare -Wmissing-declarations
NAZI= $(FLAGSBASE) -pedantic -Wconversion -Wmissing-noreturn -Wold-style-cast -Weffc++ -Wall -Wunused
CFLAGS=$(NAZI)
LDFLAGS=
EXEC=setup gen genTseitin genGraphe

all: $(EXEC)

debug: CFLAGS = $(NAZI) -D DEBUG
debug: $(EXEC)

clang: CC=clang++
clang: C11=-std=c++11
clang: $(EXEC)

purge: clean all

setup:
	mkdir -p obj

gen: obj/gen.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/gen.o: gen.cpp
	$(CC) -o $@ -c $< $(C11) $(NAZI)

genTseitin: obj/genTseitin.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/genTseitin.o: genTseitin.cpp
	$(CC) -o $@ -c $< $(C11) $(NAZI)

genGraphe: obj/genGraphe.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/genGraphe.o: genGraphe.cpp
	$(CC) -o $@ -c $< $(C11) $(NAZI)

clean:
	rm obj/*.o

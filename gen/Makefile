CC=g++
FLAGSBASE= -std=c++0x -O3 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wshadow -Wwrite-strings -Wsign-compare -Wmissing-declarations 
NAZI= $(FLAGSBASE) -pedantic -Wconversion -Wmissing-noreturn -Wold-style-cast -Weffc++ -Wall -Wunused
CFLAGS=$(NAZI)
LDFLAGS=
EXEC=gen

all: $(EXEC) 

debug: CFLAGS = $(NAZI) -D DEBUG
debug: $(EXEC)

purge: clean all

gen: obj/gen.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/gen.o: gen.cpp
	$(CC) -o $@ -c $< $(NAZI)

clean:
	rm obj/*.o

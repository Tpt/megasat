CC=g++
NAZI= -std=c++0x -O3 -Wextra -Wall -pedantic-errors -Werror -Wfatal-errors -Wcast-qual -Wcast-align -Wconversion -Wold-style-cast -Wfloat-equal -Woverloaded-virtual -Wshadow -Weffc++ -Wpointer-arith -Wunused -Wunreachable-code
CFLAGS=$(NAZI)
LDFLAGS=
EXEC=resol

all: $(EXEC)

debug: CFLAGS = $(NAZI) -D DEBUG
debug: $(EXEC)

resol: obj/clause.o obj/formule.o obj/literal.o obj/variable.o obj/CnfParser.o obj/Solveur.o obj/DavisPutnamSolveur.o obj/AbstractDPLLSolveur.o obj/DPLLSolveur.o obj/DPLLSurveilleSolveur.o obj/main.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/clause.o: src/Clause.cpp include/Clause.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
obj/formule.o: src/Formule.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
obj/literal.o: src/Literal.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
obj/variable.o: src/Variable.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/CnfParser.o: src/CnfParser.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Solveur.o: src/Solveur.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/DavisPutnamSolveur.o: src/DavisPutnamSolveur.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/AbstractDPLLSolveur.o: src/AbstractDPLLSolveur.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/DPLLSolveur.o: src/DPLLSolveur.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/DPLLSurveilleSolveur.o: src/DPLLSurveilleSolveur.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/main.o: main.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm obj/*.o

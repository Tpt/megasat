CC=g++
NAZI= -std=c++0x -O3 -Wextra -Wall -pedantic-errors -Werror -Wfatal-errors -Wcast-qual -Wcast-align -Wconversion -Wold-style-cast -Wfloat-equal -Woverloaded-virtual -Wshadow -Weffc++ -Wpointer-arith
LDFLAGS=
EXEC=resol

all: $(EXEC)

resol: obj/clause.o obj/formule.o obj/literal.o obj/variable.o obj/CnfParser.o obj/Solveur.o obj/DavisPutnamSolveur.o obj/DPLLSolveur.o obj/DPLLSurveilleSolveur.o obj/main.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/clause.o: src/Clause.cpp include/Clause.h
	$(CC) -o $@ -c $< $(NAZI)
	
obj/formule.o: src/Formule.cpp
	$(CC) -o $@ -c $< $(NAZI)
	
obj/literal.o: src/Literal.cpp
	$(CC) -o $@ -c $< $(NAZI)
	
obj/variable.o: src/Variable.cpp
	$(CC) -o $@ -c $< $(NAZI)

obj/CnfParser.o: src/CnfParser.cpp
	$(CC) -o $@ -c $< $(NAZI)

obj/Solveur.o: src/Solveur.cpp
	$(CC) -o $@ -c $< $(NAZI)

obj/DavisPutnamSolveur.o: src/DavisPutnamSolveur.cpp
	$(CC) -o $@ -c $< $(NAZI)

obj/DPLLSolveur.o: src/DPLLSolveur.cpp
	$(CC) -o $@ -c $< $(NAZI)

obj/DPLLSurveilleSolveur.o: src/DPLLSurveilleSolveur.cpp
	$(CC) -o $@ -c $< $(NAZI)

obj/main.o: main.cpp
	$(CC) -o $@ -c $< $(NAZI)
	
clean:
	rm obj/*.o

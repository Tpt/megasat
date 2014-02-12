CC=g++
NAZI= -std=c++0x -O3 -Wextra -Wall -pedantic-errors -Werror -Wfatal-errors -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wold-style-cast -Wfloat-equal -Woverloaded-virtual -Wshadow -Weffc++ -Wpointer-arith
LDFLAGS=
EXEC=resol

all: $(EXEC)

resol: clause.o formule.o literal.o variable.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

clause.o: CClause.cpp
	$(CC) -o $@ -c $< $(NAZI)
	
formule.o: CFormule.cpp
	$(CC) -o $@ -c $< $(NAZI)
	
literal.o: CLiteral.cpp
	$(CC) -o $@ -c $< $(NAZI)
	
variable.o: CVariable.cpp
	$(CC) -o $@ -c $< $(NAZI)

main.o: main.cpp
	$(CC) -o $@ -c $< $(NAZI)
	
clean:
	rm *.o
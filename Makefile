CC=g++
FLAGSBASE= -std=c++0x -O3 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wshadow -Wwrite-strings -Wsign-compare -Wmissing-declarations 
NAZI= $(FLAGSBASE) -pedantic -Wconversion -Wmissing-noreturn -Wold-style-cast -Weffc++ -Wall -Wunused
CFLAGS=$(NAZI)
LDFLAGS= 
SOLVEURS=obj/ArgumentsParser.o obj/LanceurSolveur.o obj/MessageException.o obj/Solveur.o obj/DavisPutnamSolveur.o obj/AbstractDPLLSolveur.o obj/DPLLSolveur.o obj/DPLLSurveilleSolveur.o obj/clause.o obj/formule.o obj/literal.o obj/variable.o obj/VariableNonAssigneeProvider.o
EXEC=resol tseitin colorie
LEX=flex
YACC=bison

all: $(EXEC) 

debug: CFLAGS = $(NAZI) -D DEBUG
debug: $(EXEC)

purge: clean all

colorie:  $(SOLVEURS) obj/Graphe.o obj/Arete.o obj/ColParser.o obj/CreateurContraintesColoriage.o obj/GraphvizOutput.o obj/FormuleTseitin.o obj/TransformationTseitin.o obj/main-colorie.o
	$(CC) -o $@ $^ $(LDFLAGS)

tseitin:  $(SOLVEURS) obj/LogiqueParserLogiqueParser.o obj/LogiqueParserLogiqueLexer.o obj/LogiqueParserDriver.o obj/LogiqueParserLexer.o obj/FormuleTseitin.o obj/TransformationTseitin.o obj/main-tseitin.o 
	$(CC) -o $@ $^ $(LDFLAGS)

resol:  $(SOLVEURS) obj/CnfParser.o obj/main-resol.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/clause.o: src/Clause.cpp
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

obj/VariableNonAssigneeProvider.o: src/VariableNonAssigneeProvider.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/FormuleTseitin.o: src/FormuleTseitin.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/TransformationTseitin.o: src/TransformationTseitin.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/MessageException.o: src/MessageException.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/LanceurSolveur.o: src/LanceurSolveur.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/ArgumentsParser.o: src/ArgumentsParser.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
obj/LogiqueParserLogiqueParser.o: logique_parser/logiqueParser.cpp
	$(CC) -o $@ -c $< $(FLAGSBASE)

logique_parser/logiqueParser.cpp: logique_parser/logique.y
	$(YACC) -dv -o $@ $<

obj/LogiqueParserLogiqueLexer.o: logique_parser/logiqueLexer.cpp
	$(CC) -o $@ -c $< $(FLAGSBASE)

logique_parser/logiqueLexer.cpp: logique_parser/logique.lex
	$(LEX) -o $@ $<

obj/LogiqueParserDriver.o: logique_parser/driver.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/LogiqueParserLexer.o: logique_parser/lexer.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Arete.o: src/Arete.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Graphe.o: src/Graphe.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/ColParser.o: src/ColParser.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/CreateurContraintesColoriage.o: src/CreateurContraintesColoriage.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/GraphvizOutput.o: src/GraphvizOutput.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/main-resol.o: main-resol.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/main-tseitin.o: main-tseitin.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
obj/main-colorie.o: main-colorie.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f logique_parser/logiqueLexer.cpp
	rm -f logique_parser/logiqueParser.cpp
	rm -f logique_parser/logiqueParser.hpp
	rm -f logique_parser/stack.hh
	rm obj/*.o

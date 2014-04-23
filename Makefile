CC=g++
C11= -std=c++0x
FLAGSBASE= -O3 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wshadow -Wwrite-strings -Wsign-compare -Wmissing-declarations 
NAZIBASE= $(FLAGSBASE) -pedantic -Wconversion -Wmissing-noreturn -Wold-style-cast -Weffc++ -Wall -Wunused -Wsign-conversion -Wunused -Wstrict-aliasing -Wstrict-overflow -Wconversion -Wdisabled-optimization
ifeq ($(CC), g++)
    NAZI= $(NAZIBASE) -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wlogical-op -Wunsafe-loop-optimizations
else
    NAZI=$(NAZIBASE)
endif
CFLAGS=$(NAZI)
LDFLAGS= 
SOLVEURS=obj/ArgumentsParser.o obj/LanceurSolveur.o obj/MessageException.o obj/Solveur.o obj/DavisPutnamSolveur.o obj/AbstractDPLLSolveur.o obj/DPLLSolveur.o obj/DPLLSurveilleSolveur.o obj/MinisatSolveur.o obj/clause.o obj/formule.o obj/.o obj/literal.o obj/variable.o obj/VariableNonAssigneeProvider.o obj/GestionConflits.o obj/Preuve.o obj/LatexPrinter.o obj/ConstructeurPreuve.o obj/GraphvizConflitOutput.o
EXEC=setup resol tseitin colorie
LEX=flex
YACC=bison

all: $(EXEC) 

debug: CFLAGS = $(NAZI) -D DEBUG -g
debug: FLAGSBASE = $(FLAGSBASE) -D DEBUG -g
debug: $(EXEC)

purge: clean all

clang: CC=clang++
clang: C11=-std=c++11
clang: $(EXEC)

setup:
	mkdir -p obj

colorie:  $(SOLVEURS) obj/Graphe.o obj/Arete.o obj/ColParser.o obj/CreateurContraintesColoriage.o obj/GraphvizColoriageOutput.o obj/FormuleTseitin.o obj/TransformationTseitin.o obj/main-colorie.o
	$(CC) -o $@ $^ $(LDFLAGS)

tseitin:  $(SOLVEURS) obj/LogiqueParserLogiqueParser.o obj/LogiqueParserLogiqueLexer.o obj/LogiqueParserDriver.o obj/LogiqueParserLexer.o obj/FormuleTseitin.o obj/TransformationTseitin.o obj/main-tseitin.o 
	$(CC) -o $@ $^ $(LDFLAGS)

resol:  $(SOLVEURS) obj/CnfParser.o obj/main-resol.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/clause.o: src/Clause.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/formule.o: src/Formule.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/literal.o: src/Literal.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/variable.o: src/Variable.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/CnfParser.o: src/CnfParser.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/Solveur.o: src/Solveur.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/DavisPutnamSolveur.o: src/DavisPutnamSolveur.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/AbstractDPLLSolveur.o: src/AbstractDPLLSolveur.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/DPLLSolveur.o: src/DPLLSolveur.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/DPLLSurveilleSolveur.o: src/DPLLSurveilleSolveur.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/MinisatSolveur.o: src/MinisatSolveur.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/VariableNonAssigneeProvider.o: src/VariableNonAssigneeProvider.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/GestionConflits.o: src/GestionConflits.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

obj/FormuleTseitin.o: src/FormuleTseitin.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/TransformationTseitin.o: src/TransformationTseitin.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/MessageException.o: src/MessageException.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/LanceurSolveur.o: src/LanceurSolveur.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
		
obj/.o: tests/.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/ArgumentsParser.o: src/ArgumentsParser.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/LogiqueParserLogiqueParser.o: logique_parser/logiqueParser.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

logique_parser/logiqueParser.cpp: logique_parser/logique.y
	$(YACC) -dv -o $@ $<

obj/LogiqueParserLogiqueLexer.o: logique_parser/logiqueLexer.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

logique_parser/logiqueLexer.cpp: logique_parser/logique.lex
	$(LEX) -o $@ $<

obj/LogiqueParserDriver.o: logique_parser/driver.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

obj/LogiqueParserLexer.o: logique_parser/lexer.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

obj/Arete.o: src/Arete.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/Graphe.o: src/Graphe.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/ColParser.o: src/ColParser.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/CreateurContraintesColoriage.o: src/CreateurContraintesColoriage.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/GraphvizColoriageOutput.o: src/GraphvizColoriageOutput.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/GraphvizConflitOutput.o: src/GraphvizConflitOutput.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/Preuve.o: src/Preuve.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/LatexPrinter.o: src/LatexPrinter.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/ConstructeurPreuve.o: src/ConstructeurPreuve.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/main-resol.o: main-resol.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/main-tseitin.o: main-tseitin.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/main-colorie.o: main-colorie.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

clean:
	rm -f logique_parser/logiqueLexer.cpp
	rm -f logique_parser/logiqueParser.cpp
	rm -f logique_parser/logiqueParser.hpp
	rm -f logique_parser/stack.hh
	rm obj/*.o

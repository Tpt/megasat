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
SOLVEURS=obj/ArgumentsParser.o obj/LanceurSolveur.o obj/MessageException.o obj/Solveur.o obj/DavisPutnamSolveur.o obj/AbstractDPLLSolveur.o obj/DPLLSolveur.o obj/DPLLSurveilleSolveur.o obj/MinisatSolveur.o obj/clause.o obj/formule.o obj/.o obj/literal.o obj/variable.o obj/VariableNonAssigneeProvider.o obj/GestionConflits.o obj/Preuve.o obj/LatexPrinter.o obj/ConstructeurPreuve.o obj/GraphvizConflitOutput.o obj/TheorieGreffon.o
EXEC=setup resol tseitin colorie
EXEC=setup resol tseitin colorie congruence_solver difference_solver
LEX=flex
YACC=bison

all: $(EXEC) 

debug: CFLAGS = $(NAZI) -D DEBUG -g
debug: FLAGSBASE = -O3 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wshadow -Wwrite-strings -Wsign-compare -Wmissing-declarations -D DEBUG -g
debug: $(EXEC)

purge: clean all

clang: CC=clang++
clang: C11=-std=c++11
clang: $(EXEC)

setup:
	mkdir -p obj

colorie:  $(SOLVEURS) obj/Graphe.o obj/Arete.o obj/ColParser.o obj/CreateurContraintesColoriage.o obj/GraphvizColoriageOutput.o obj/main-colorie.o
	$(CC) -o $@ $^ $(LDFLAGS)

tseitin:  $(SOLVEURS) obj/LogiqueParserLogiqueParser.o obj/LogiqueParserLogiqueLexer.o obj/LogiqueParserDriver.o obj/LogiqueParserLexer.o obj/main-tseitin.o 
	$(CC) -o $@ $^ $(LDFLAGS)

resol:  $(SOLVEURS) obj/CnfParser.o obj/main-resol.o
	$(CC) -o $@ $^ $(LDFLAGS)

congruence_solver:  $(SOLVEURS) obj/CongruenceParserLogiqueParser.o obj/CongruenceParserLogiqueLexer.o obj/CongruenceParserDriver.o obj/CongruenceParserLexer.o obj/Terme.o obj/AtomeCongruence.o obj/TheorieGreffon.o obj/TheorieGreffonCongruence.o obj/main-congruence.o
	$(CC) -o $@ $^ $(LDFLAGS)

difference_solver:  $(SOLVEURS) obj/DifferenceParserLogiqueParser.o obj/DifferenceParserLogiqueLexer.o obj/DifferenceParserDriver.o obj/DifferenceParserLexer.o obj/AtomeDifference.o obj/TheorieGreffon.o obj/TheorieGreffonDifference.o obj/main-difference.o
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

obj/TheorieGreffon.o: src/TheorieGreffon.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)
	
obj/TheorieGreffonCongruence.o: src/TheorieGreffonCongruence.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/TheorieGreffonDifference.o: src/TheorieGreffonDifference.cpp
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
	
obj/LogiqueParserLogiqueParser.o: parser/logique/logiqueParser.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

parser/logique/logiqueParser.cpp: parser/logique/logique.y
	$(YACC) -dv -o $@ $<

obj/LogiqueParserLogiqueLexer.o: parser/logique/logiqueLexer.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

parser/logique/logiqueLexer.cpp: parser/logique/logique.lex
	$(LEX) -o $@ $<

obj/LogiqueParserDriver.o: parser/logique/driver.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

obj/LogiqueParserLexer.o: parser/logique/lexer.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

obj/CongruenceParserLogiqueParser.o: parser/congruence/congruenceParser.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

parser/congruence/congruenceParser.cpp: parser/congruence/congruence.y
	$(YACC) -dv -o $@ $<

obj/CongruenceParserLogiqueLexer.o: parser/congruence/congruenceLexer.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

parser/congruence/congruenceLexer.cpp: parser/congruence/congruence.lex
	$(LEX) -o $@ $<

obj/CongruenceParserDriver.o: parser/congruence/driver.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

obj/CongruenceParserLexer.o: parser/congruence/lexer.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

obj/DifferenceParserLogiqueParser.o: parser/difference/differenceParser.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

parser/difference/differenceParser.cpp: parser/difference/difference.y
	$(YACC) -dv -o $@ $<

obj/DifferenceParserLogiqueLexer.o: parser/difference/differenceLexer.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

parser/difference/differenceLexer.cpp: parser/difference/difference.lex
	$(LEX) -o $@ $<

obj/DifferenceParserDriver.o: parser/difference/driver.cpp
	$(CC) -o $@ -c $< $(C11) $(FLAGSBASE)

obj/DifferenceParserLexer.o: parser/difference/lexer.cpp
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
	
obj/Terme.o: src/Terme.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/AtomeCongruence.o: src/AtomeCongruence.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/AtomeDifference.o: src/AtomeDifference.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/main-resol.o: main-resol.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

obj/main-tseitin.o: main-tseitin.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/main-colorie.o: main-colorie.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/main-congruence.o: main-congruence.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/main-difference.o: main-difference.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)

clean:
	rm -f parser/*/*Lexer.cpp
	rm -f parser/*/*Parser.cpp
	rm -f parser/*/*Parser.hpp
	rm -f parser/*/*Parser.output
	rm -f parser/*/stack.hh
	rm -f parser/*/location.hh
	rm -f parser/*/position.hh
	rm -f obj/*.o

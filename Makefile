CC=g++
NAZI= -std=c++0x -O3 -Wextra -Wall -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunused -Wunreachable-code
CFLAGS=$(NAZI)
LDFLAGS=
EXEC=resol
LEX=flex
YACC=bison

all: resol tseitin

debug: CFLAGS = $(NAZI) -D DEBUG
debug: $(EXEC)

tseitin:  obj/clause.o obj/formule.o obj/literal.o obj/variable.o obj/Solveur.o obj/DavisPutnamSolveur.o obj/AbstractDPLLSolveur.o obj/DPLLSolveur.o obj/DPLLSurveilleSolveur.o obj/ParseError.o obj/LogiqueParserLogiqueParser.o obj/LogiqueParserLogiqueLexer.o obj/LogiqueParserDriver.o obj/LogiqueParserLexer.o obj/Connecteurs.o obj/ConvertisseurFormuleTseitin.o obj/TransformationTseitin.o obj/main-tseitin.o
	$(CC) -o $@ $^ $(LDFLAGS)

resol: obj/clause.o obj/formule.o obj/literal.o obj/variable.o obj/CnfParser.o obj/Solveur.o obj/DavisPutnamSolveur.o obj/AbstractDPLLSolveur.o obj/DPLLSolveur.o obj/DPLLSurveilleSolveur.o obj/VariableNonAssigneeProvider.o obj/ParseError.o obj/main-resol.o
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

obj/VariableNonAssigneeProvider.o: src/VariableNonAssigneeProvider.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/Connecteurs.o: src/Connecteurs.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/TransformationTseitin.o: src/TransformationTseitin.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/ConvertisseurFormuleTseitin.o: src/ConvertisseurFormuleTseitin.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/ParseError.o: src/ParseError.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/LogiqueParserLogiqueParser.o: logique_parser/logiqueParser.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

logique_parser/logiqueParser.cpp: logique_parser/logique.y
	$(YACC) -dv -o $@ $<

obj/LogiqueParserLogiqueLexer.o: logique_parser/logiqueLexer.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

logique_parser/logiqueLexer.cpp: logique_parser/logique.lex
	$(LEX) -o $@ $<

obj/LogiqueParserDriver.o: logique_parser/driver.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/LogiqueParserLexer.o: logique_parser/lexer.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/main-resol.o: main-resol.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

obj/main-tseitin.o: main-tseitin.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm -f logique_parser/logiqueLexer.cpp
	rm -f logique_parser/logiqueParser.cpp
	rm -f logique_parser/logiqueParser.hpp
	rm obj/*.o

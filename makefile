CC = gcc
MAIN = ./programas
BIN = ./bin
SRC = ./src
INCLUDE = ./include
OBJ = ./obj
FLAG = -O3 -g3  -W -Wall -Wextra -Wuninitialized -Wstrict-aliasing -std=c11 

IMPLEMENT_SEQ = jacobiseq
IMPLEMENT_PAR = jacobipar
PROG_SEQ = main_seq
PROG_PAR = main_par


seq:
	${CC} $(FLAG) -c $(SRC)/$(IMPLEMENT_SEQ).c -I $(INCLUDE) -o $(OBJ)/$(IMPLEMENT_SEQ).out -lm
	${CC} $(FLAG) $(MAIN)/$(PROG_SEQ).c $(OBJ)/*.out -I $(INCLUDE) -o $(BIN)/$(PROG_SEQ) -lm
	$(BIN)/$(PROG_SEQ)


par:
	${CC} $(FLAG) -c $(SRC)/$(IMPLEMENT_PAR).c -I $(INCLUDE) -o $(OBJ)/$(IMPLEMENT_PAR).out -lm
	${CC} $(FLAG) $(MAIN)/$(PROG_PAR).c $(OBJ)/*.out -I $(INCLUDE) -o $(BIN)/$(PROG_PAR) -lm
	$(BIN)/$(PROG_PAR)

clean:
	rm $(OBJ)/*
	rm $(BIN)/*
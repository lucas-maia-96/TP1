#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa geracarga
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2022-05-31 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm 
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/geracarga.o
HDRS = $(INC)/msgassert.h
CFLAGS = -g -Wall -c -I$(INC)

EXE = $(BIN)/geracarga

all: use

use: $(EXE)
	$(EXE) -o ../entrada.txt -r 20 -j 8 -v 5

$(BIN)/geracarga: $(OBJS)
	$(CC) -g -o $(BIN)/geracarga $(OBJS) $(LIBS)

$(OBJ)/geracarga.o: $(HDRS) $(SRC)/geracarga.c
	$(CC) $(CFLAGS) -o $(OBJ)/geracarga.o $(SRC)/geracarga.c 

clean:
	rm -f $(EXE) $(OBJS)  

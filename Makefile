# Arquivos a serem compilados
OBJS = main.cpp src/ponto.cpp

# Compilador
CC = g++

COMPILER_FLAGS = -w

# flags por causa do glad, opengl, etc.
LINKER_FLAGS = -Iinclude

# Arquivo de saida
OBJ_NAME = main.out

# Comando para compilar
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
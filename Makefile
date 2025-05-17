# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = build
BIN = frogger

# Lista de arquivos .c e .o
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Regra para compilar .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para linkar o executável
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

# Alvo padrão: compilar tudo
all: $(BIN)

# Regra para executar o jogo
run: all
	./$(BIN)

# Limpar objetos e executável
clean:
	rm -rf $(OBJ_DIR) $(BIN)

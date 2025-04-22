# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -g -I./include
LDFLAGS = -lreadline

# Dossiers du projet
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
OBJ_DIR = obj

# Création des dossiers si inexistants
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

# Fichiers source et objets
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nom de l'exécutable
TARGET = $(BIN_DIR)/shell

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Nettoyage complet (inclut les dossiers générés)
distclean: clean
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Règle pour reconstruire tout
rebuild: distclean all

# Indique que ces cibles ne sont pas des fichiers
.PHONY: all clean distclean rebuild
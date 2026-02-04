# Nom de l'exécutable
TARGET = game

# Compilateur
CC = gcc

# Flags de compilation
CFLAGS = -Wall -Wextra -std=c99

# Liens Raylib (Linux)
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

# Récupère automatiquement tous les fichiers .c dans src/
SRC = $(shell find src -name "*.c")

# Génère les .o pour chaque .c
OBJ = $(SRC:.c=.o)

# Règle par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Compilation des .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Supprimer les .o et le jeu
clean:
	rm -f $(OBJ) $(TARGET)

# Lancer le jeu après compilation
run: all
	./$(TARGET)

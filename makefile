# Nom de l'exécutable
TARGET = game

# Compilateur
CC = gcc

# Flags de compilation
CFLAGS = -Wall -Wextra -std=c99

# Liens Raylib et dépendances Linux
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

# Tous les fichiers .c du projet dans le bon ordre
SRC = core/GameManager.c player/PlayerMovement.c player/PlayerController.c levels/LevelManager.c main.c


# Fichiers objets correspondants
OBJ = $(SRC:.c=.o)

# Règle par défaut : build
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Supprimer les .o et l'exécutable
clean:
	rm -f $(OBJ) $(TARGET)

# Lancer le jeu
run: all
	./$(TARGET)

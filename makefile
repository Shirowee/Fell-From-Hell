# Nom de l'exécutable
TARGET = game

# Compilateur
CC = gcc

# Flags de compilation
# -I indique où est raylib.h
CFLAGS = -Wall -Wextra -std=c99 -I./raylib

# Librairies : raylib + dépendances Linux
# -L indique où est libraylib.a
LIBS = -L./raylib -lraylib -lm -lpthread -ldl -lrt -lX11

# Tous les fichiers .c de ton projet dans les sous-dossiers
SRC = \
    main.c \
    core/GameManager.c \
    player/PlayerController.c \
    player/PlayerMovement.c \
    levels/LevelManager.c

# Création des .o
OBJ = $(SRC:.c=.o)

# Règle principale
all: $(TARGET)

# Link final
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Compilation des .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(TARGET)

# Lancer le jeu
run: all

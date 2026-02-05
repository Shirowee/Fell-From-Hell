# Nom de l'exécutable
TARGET = game

# Compilateur
CC = gcc

# Détection de l'OS
ifeq ($(OS),Windows_NT)
    PLATFORM = WINDOWS
else
    PLATFORM = LINUX
endif

# Flags communs
CFLAGS = -Wall -Wextra -std=c99 -I./raylib

# Sources
SRC = \
    main.c \
    core/GameManager.c \
    player/PlayerController.c \
    player/PlayerMovement.c \
    levels/LevelManager.c

OBJ = $(SRC:.c=.o)

# -----------------------------
# Librairies selon plateforme
# -----------------------------

ifeq ($(PLATFORM),WINDOWS)
    LIBS = raylib/libraylib.a -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
else
    LIBS = raylib/libraylib.a -lm -lpthread -ldl -lrt
    RM = rm -f
endif

# -----------------------------
# Règles
# -----------------------------

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TARGET)

run: all
	./$(TARGET)

# --- CONFIGURATION DES FICHIERS ---
TARGET_NAME = game
SRC = main.c \
      core/GameManager.c \
      player/PlayerController.c \
      player/PlayerMovement.c \
      levels/LevelManager.c

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -std=c99 -O2 -I./raylib/include

# --- LOGIQUE DE DÉTECTION ---

# 1. On vérifie si on est sur Windows natif ou si on a le cross-compiler
ifeq ($(OS),Windows_NT)
    # On est physiquement sous Windows
    CC = gcc
    TARGET = $(TARGET_NAME).exe
    LIBS = raylib/windows/libraylib.a -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
    PLATFORM_FOUND = WINDOWS_NATIVE
else ifneq ($(shell which x86_64-w64-mingw32-gcc 2>/dev/null),)
    # On est sous Linux/WSL mais le cross-compiler est installé
    CC = x86_64-w64-mingw32-gcc
    TARGET = $(TARGET_NAME).exe
    LIBS = raylib/windows/libraylib.a -lopengl32 -lgdi32 -lwinmm
    RM = rm -f
    PLATFORM_FOUND = WINDOWS_CROSS
else
    # Fallback : Rien pour Windows n'est trouvé, on compile pour Linux
    CC = gcc
    TARGET = $(TARGET_NAME)
    LIBS = raylib/linux/libraylib.a -lm -lpthread -ldl -lrt -lX11
    RM = rm -f
    PLATFORM_FOUND = LINUX_FALLBACK
endif

# --- RÈGLES DE COMPILATION ---

all: $(TARGET)
	@echo "--- Mode de compilation : $(PLATFORM_FOUND) ---"

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TARGET)

run: all
	@if [ "$(TARGET)" = "$(TARGET_NAME).exe" ]; then \
		echo "Lancement de l'exécutable Windows..."; \
		./$(TARGET); \
	else \
		echo "Lancement de l'exécutable Linux..."; \
		./$(TARGET); \
	fi
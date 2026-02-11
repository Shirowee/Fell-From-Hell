# --- CONFIGURATION DU NOM ---
TARGET_NAME = bin/game

# --- DÉTECTION AUTOMATIQUE DES SOURCES ---
# On cherche tous les .c dans le dossier courant et les sous-dossiers (core, player, levels)
SRC = $(wildcard src/*.c) \
      $(wildcard src/core/*.c) \
      $(wildcard src/player/*.c) \
      $(wildcard src/levels/*.c)

# On transforme la liste des .c en .o pour la compilation
OBJ = $(SRC:.c=.o)

# Flags de compilation
CFLAGS = -Wall -Wextra -std=c99 -O2 -I./raylib/include

# --- LOGIQUE DE DÉTECTION DE PLATEFORME (WINDOWS FIRST) ---

# Vérification si on est sur Windows natif
ifeq ($(OS),Windows_NT)
    CC = gcc
    TARGET = $(TARGET_NAME).exe
    LIBS = raylib/windows/libraylib.a -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
    PLATFORM_STATUS = WINDOWS_NATIVE
else 
    # Sinon, on vérifie si le compilateur croisé Windows existe (WSL)
    MINGW_CHECK := $(shell which x86_64-w64-mingw32-gcc 2>/dev/null)
    ifneq ($(MINGW_CHECK),)
        CC = x86_64-w64-mingw32-gcc
        TARGET = $(TARGET_NAME).exe
        LIBS = raylib/windows/libraylib.a -lopengl32 -lgdi32 -lwinmm
        RM = rm -f
        PLATFORM_STATUS = WINDOWS_CROSS_COMPILATION
    else
        # Fallback ultime : Compilation Linux
        CC = gcc
        TARGET = $(TARGET_NAME)
        LIBS = raylib/linux/libraylib.a -lm -lpthread -ldl -lrt -lX11
        RM = rm -f
        PLATFORM_STATUS = LINUX_FALLBACK
    endif
endif

# --- RÈGLES DE COMPILATION ---

all: $(TARGET)
	@echo "------------------------------------------------"
	@echo "Compilation réussie : $(TARGET)"
	@echo "Mode détecté : $(PLATFORM_STATUS)"
	@echo "Fichiers inclus : $(SRC)"
	@echo "------------------------------------------------"

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Règle générique pour les .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TARGET)

run: all
	./$(TARGET)
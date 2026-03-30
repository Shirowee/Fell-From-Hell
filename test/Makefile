# ==============================
# CONFIGURATION
# ==============================

# --- Nom du dossier de sortie ---
BIN_DIR = ../bin

# --- Détection automatique des sources projet (sans main.c) ---
PROJECT_SRC = $(wildcard ../src/core/*.c) \
              $(wildcard ../src/enemies/*.c) \
              $(wildcard ../src/levels/*.c) \
              $(wildcard ../src/systems/*.c) \
              $(wildcard ../src/player/*.c)

PROJECT_OBJ = $(PROJECT_SRC:.c=.o)

# --- Détection automatique des fichiers de test ---
TEST_SRC = $(wildcard *.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Génération automatique des exécutables dans ../bin
TEST_EXE = $(TEST_SRC:%.c=$(BIN_DIR)/%.exe)

# Flags de compilation
BASE_CFLAGS = -Wall -Wextra -std=c99 -I../raylib/include
CFLAGS = $(BASE_CFLAGS) -02
debug: CFLAGS = $(BASE_CFLAGS) -g -O0
debug: clean all

# ==============================
# DÉTECTION PLATEFORME
# ==============================

ifeq ($(OS),Windows_NT)
    CC = gcc
    LIBS = ../raylib/windows/libraylib.a ../lib/cJson/libcjson_win.a -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
    MKDIR = if not exist $(BIN_DIR) mkdir $(BIN_DIR)
    PLATFORM_STATUS = WINDOWS_NATIVE
else 
    MINGW_CHECK := $(shell which x86_64-w64-mingw32-gcc 2>/dev/null)
    ifneq ($(MINGW_CHECK),)
        CC = x86_64-w64-mingw32-gcc
        LIBS = ../raylib/windows/libraylib.a ../lib/cJson/libcjson_win.a -lopengl32 -lgdi32 -lwinmm
        RM = rm -f
        MKDIR = mkdir -p $(BIN_DIR)
        PLATFORM_STATUS = WINDOWS_CROSS_COMPILATION
    else
        CC = gcc
        LIBS = ../raylib/linux/libraylib.a ../lib/cJson/libcjson_linux.a -lm -lpthread -ldl -lrt -lX11
        RM = rm -f
        MKDIR = mkdir -p $(BIN_DIR)
        PLATFORM_STATUS = LINUX_FALLBACK
    endif
endif

# ==============================
# RÈGLES
# ==============================

all: prepare $(TEST_EXE)
	@echo "------------------------------------------------"
	@echo "Tests compilés : $(TEST_EXE)"
	@echo "Mode détecté : $(PLATFORM_STATUS)"
	@echo "Sources projet : $(PROJECT_SRC)"
	@echo "------------------------------------------------"

# Création du dossier bin si nécessaire
prepare:
	@$(MKDIR)

# Génération d'un .exe par test
$(BIN_DIR)/%.exe: %.o $(PROJECT_OBJ)
	$(CC) $^ -o $@ $(LIBS)

# Règle générique .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean complet
clean:
	$(RM) $(PROJECT_OBJ) $(TEST_OBJ) $(BIN_DIR)/*.exe

# Exécution automatique des tests
run: all
	@for exe in $(TEST_EXE); do \
		echo "Running $$exe"; \
		./$$exe; \
	done
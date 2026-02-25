# ==============================
# CONFIGURATION
# ==============================

# Sources du projet (sans main.c)
PROJECT_SRC = \
              $(wildcard ../src/core/*.c) \
              $(wildcard ../src/enemies/*.c) \
              $(wildcard ../src/levels/*.c) \
              $(wildcard ../src/player/*.c)

PROJECT_OBJ = $(PROJECT_SRC:.c=.o)

# Fichiers de test
TEST_SRC = $(wildcard *.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Noms des exécutables (même nom que les .c)
TEST_EXE = $(TEST_SRC:.c=.exe)

CFLAGS = -Wall -Wextra -std=c99 -O2

# ==============================
# DÉTECTION PLATEFORME
# ==============================

ifeq ($(OS),Windows_NT)
    CC = gcc
    LIBS = ../raylib/windows/libraylib.a -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
else 
    MINGW_CHECK := $(shell which x86_64-w64-mingw32-gcc 2>/dev/null)
    ifneq ($(MINGW_CHECK),)
        CC = x86_64-w64-mingw32-gcc
        LIBS = ../raylib/windows/libraylib.a -lopengl32 -lgdi32 -lwinmm
        RM = rm -f
    else
        CC = gcc
        LIBS = ../raylib/linux/libraylib.a -lm -lpthread -ldl -lrt -lX11
        RM = rm -f
    endif
endif

# ==============================
# RULES
# ==============================

# Noms des exécutables dans ../bin
TEST_EXE = $(TEST_SRC:%.c=../bin/%.exe)

all: $(TEST_EXE)
	@echo "-----------------------------"
	@echo "Tests compilés dans ../bin :"
	@echo "$(TEST_EXE)"
	@echo "-----------------------------"

# Génération d'un exe par test dans ../bin
../bin/%.exe: %.o $(PROJECT_OBJ)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(PROJECT_OBJ) $(TEST_OBJ) *.exe

run: all
	@for exe in $(TEST_EXE); do ./$$exe; done
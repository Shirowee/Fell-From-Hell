TARGET = game
CC = gcc

ifeq ($(OS),Windows_NT)
    PLATFORM = WINDOWS
else
    PLATFORM = LINUX
endif

CFLAGS = -Wall -Wextra -std=c99 -O2 -I./raylib/include

SRC = \
    main.c \
    core/GameManager.c \
    player/PlayerController.c \
    player/PlayerMovement.c \
    levels/LevelManager.c

OBJ = $(SRC:.c=.o)

ifeq ($(PLATFORM),WINDOWS)
    LIBS = raylib/windows/libraylib.a -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
else
    LIBS = raylib/linux/libraylib.a -lm -lpthread -ldl -lrt -lX11
    RM = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TARGET)

run: all
	./$(TARGET)

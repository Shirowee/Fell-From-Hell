#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../raylib/include/raylib.h"

// Sous Structure
typedef struct {
    int x;
    int y;
} Pos;

typedef struct {
    float x, y, w, h;
} Rect;

typedef struct {
    char type[32];
    int solid; // 1 pour vrai, 0 pour faux
    float x, y, width, high;
    Rectangle rect; 
    Color color;

} Platform;

#endif

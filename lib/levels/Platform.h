#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../raylib/include/raylib.h"

typedef struct Platform {
    Rectangle rect;
    bool solid;
} Platform;

#endif

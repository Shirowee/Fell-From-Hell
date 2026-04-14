#include "../../lib/core/ResolutionManager.h"
#include "../../raylib/include/raylib.h"

ResolutionConfig resolution;

void ResolutionInit(int mapRefWidth, int screenWidth, int screenHeight) {
    resolution.screenW = screenWidth;
    resolution.screenH = screenHeight;
    resolution.scale = (float)GetScreenWidth() / mapRefWidth;
}

float RS(float value) {
    return value * resolution.scale;
}
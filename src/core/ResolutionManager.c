#include "../../lib/core/ResolutionManager.h"
#include "../../raylib/include/raylib.h"

ResolutionConfig resolution;

void ResolutionInit(int mapRefWidth, int mapRefHeight) {
    resolution.refW   = mapRefWidth;
    resolution.refH   = mapRefHeight;
    resolution.scale  = (float)GetScreenWidth() / mapRefWidth;
}

float ResScale(float value) {
    return value * resolution.scale;
}
#include "LevelManager.h"
#include "Platform.h"
#include "raylib.h"

static Platform ground;

void LevelInit(void)
{
    ground.rect = (Rectangle){ 0, 400, 800, 50 };
}

void LevelDraw(void)
{
    DrawRectangleRec(ground.rect, DARKGRAY);
}

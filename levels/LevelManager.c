#include "LevelManager.h"
#include "Platform.h"
#include "raylib.h"

// Sol unique du niveau
static Platform ground;

//init le sol
void LevelInit(void)
{
    ground.rect = (Rectangle){ 0, 400, 800, 50 };
}


//dessine le sol
void LevelDraw(void)
{
    DrawRectangleRec(ground.rect, DARKGRAY);
}

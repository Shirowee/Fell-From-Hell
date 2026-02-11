#include "../../lib/levels/LevelManager.h"
#include "../../lib/levels/Platform.h"
#include "../../raylib/include/raylib.h"

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

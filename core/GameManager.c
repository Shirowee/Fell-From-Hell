#include "GameManager.h"
#include "raylib.h"
#include "../player/PlayerController.h"
#include "../levels/LevelManager.h"

void GameInit(void)
{
    PlayerInit();
    LevelInit();
}

void GameUpdate(void)
{
    PlayerUpdate();
}

void GameDraw(void)
{
    LevelDraw();
    PlayerDraw();
}

void GameUnload(void)
{
    // Rien encore
}

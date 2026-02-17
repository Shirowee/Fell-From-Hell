#include "../../lib/core/GameManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/PlayerController.h"
#include "../../lib/levels/LevelManager.h"

//initialise le jeu
void GameInit(void)
{
    PlayerInit();
    LevelInit();
}

//maj du jeu
void GameUpdate(void)
{
    Platform *platforms[1] = { &ground };
    PlayerUpdate(platforms, 1);
}

//rendre le jeu
void GameDraw(void)
{
    LevelDraw();
    PlayerDraw();
}

//décharger
void GameUnload(void)
{
    // Rien pour l'instant
}

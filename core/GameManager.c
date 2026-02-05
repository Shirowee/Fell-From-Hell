#include "GameManager.h"
#include "../raylib/raylib.h"
#include "../player/PlayerController.h"
#include "../levels/LevelManager.h"

//initialise le jeu
void GameInit(void)
{
    PlayerInit();
    LevelInit();
}

//maj du jeu
void GameUpdate(void)
{
    PlayerUpdate();
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

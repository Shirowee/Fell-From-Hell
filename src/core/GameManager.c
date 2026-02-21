#include "../../lib/core/GameManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/PlayerController.h"
#include "../../lib/levels/LevelManager.h"

//initialise le jeu
void GameInit(Player *player)
{
    PlayerInit(player);
    LevelInit();
}

//maj du jeu
void GameUpdate(Player *player)
{
    Platform *platforms[1] = { &ground };
    PlayerUpdate(player, platforms, 1);
}

//rendre le jeu
void GameDraw(Player *player)
{
    LevelDraw();
    PlayerDraw(player);
}

//décharger
void GameUnload(void)
{
    // Rien pour l'instant
}

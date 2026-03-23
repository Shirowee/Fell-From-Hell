#include "../../lib/core/GameManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/PlayerController.h"
#include "../../lib/levels/LevelManager.h"

//initialise le jeu
void GameInit(Player *player,float dynamicTileSize)
{
    LevelInit(dynamicTileSize);
    PlayerInit(player);
}

//maj du jeu
void GameUpdate(Player *player)
{
    
    PlayerUpdate(player, currentLevel.platforms, currentLevel.platformCount);
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

#include "../../lib/core/GameManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/PlayerController.h"
#include "../../lib/levels/LevelManager.h"

//initialise le jeu
void GameInit(Player *player,float dynamicTileSize)
{
    LevelInit(dynamicTileSize);
    PlayerInit(player);
    srand(time(NULL));
    InitBulletPool(&playerBulletPool, 300);
}

//maj du jeu
void GameUpdate(Player *player, double* timeSpent, double* startReload)
{
    
    PlayerUpdate(player, currentLevel.platforms, currentLevel.platformCount, timeSpent, startReload);
    UpdateBulletPool(&playerBulletPool);
}

//rendre le jeu
void GameDraw(Player *player)
{
    LevelDraw();
    PlayerDraw(player);
    DrawBulletPool(&playerBulletPool);
}

//décharger
void GameUnload(void)
{
    FreeBulletPool(&playerBulletPool);
    CloseWindow();
}

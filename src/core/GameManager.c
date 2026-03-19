#include "../../lib/core/GameManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/PlayerController.h"
#include "../../lib/levels/LevelManager.h"

//initialise le jeu
void GameInit(Player *player,float dynamicTileSize)
{
    PlayerInit(player);
    LevelInit(dynamicTileSize);
}

//maj du jeu
void GameUpdate(Player *player)
{
    Platform *activePlatforms[MAX_PLATFORMS];
    for(int i = 0; i < currentLevel.platformCount; i++){ // Conversion des pointeurs pour PlayerUpdate
        activePlatforms[i] = &currentLevel.platforms[i];
    }
    PlayerUpdate(player, activePlatforms, currentLevel.platformCount);
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

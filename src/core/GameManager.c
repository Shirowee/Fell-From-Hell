#include "../../lib/core/GameManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/PlayerController.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/systems/EnemyPool.h"
#include "../../lib/systems/EnemySpawner.h"
#include "../../lib/systems/CollisionSystem.h"
#include "../../lib/systems/LifeManager.h"

//initialise le jeu
void GameInit(Player *player)
{
    LevelInit();
    PlayerInit(player);

    //Init enemy
    InitEnemyPool(&enemyPool, 100);
    EnemySpawnerInit(&enemySpawner);
    InitBulletPool(&bulletPool, 3000);

    srand(time(NULL));
    InitBulletPool(&playerBulletPool, 300);
}

//maj du jeu
void GameUpdate(Player *player, double* timeSpent, double* startReload)
{
    UpdateEnemySpawner(&enemySpawner, &enemyPool);
    UpdateEnemyPool(&enemyPool, getPlayerCenter(player));
    UpdateBulletPool(&bulletPool);

    CheckEnemyBulletCollision(&enemyPool, &playerBulletPool);

    PlayerUpdate(player, currentLevel.platforms, currentLevel.platformCount, timeSpent, startReload);
    UpdateBulletPool(&playerBulletPool);
}

//rendre le jeu
void GameDraw(Player *player)
{
    LevelDraw();
    PlayerDraw(player);
    DrawEnemyPool(&enemyPool);
    DrawBulletPool(&playerBulletPool, player->position);
    DrawBulletPool(&bulletPool, player->position);
}

//décharger
void GameUnload(void)
{
    FreeBulletPool(&playerBulletPool);
    FreeEnemyPool(&enemyPool);
    CloseWindow();
}

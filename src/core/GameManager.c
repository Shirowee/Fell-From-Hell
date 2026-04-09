#include "../../lib/core/GameManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/PlayerController.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/systems/EnemyPool.h"
#include "../../lib/systems/EnemySpawner.h"
#include "../../lib/systems/CollisionSystem.h"
#include "../../lib/systems/TriggerSystem.h"

// Initialise le jeu
void GameInit(Player *player)
{
    LevelInit();
    PlayerInit(player);

    //Init enemy
    InitEnemyPool(&enemyPool, 100);
    EnemySpawnerInit(&enemySpawner);

    srand(time(NULL));
    InitBulletPool(&playerBulletPool, 300);
}

// Mise a jour du jeu
void GameUpdate(Player *player, double* timeSpent, double* startReload)
{
    NextLvlUpdate(player, &enemyPool, &playerBulletPool);
    UpdateEnemySpawner(&enemySpawner, &enemyPool);
    UpdateEnemyPool(&enemyPool, player->position);
    UpdateBulletPool(&playerBulletPool);

    CheckEnemyBulletCollision(&enemyPool, &playerBulletPool);

    PlayerUpdate(player, currentLevel.platforms, currentLevel.platformCount, timeSpent, startReload);
    TriggerSystemUpdate(player, &currentLevel);
    UpdateBulletPool(&playerBulletPool);
}

// Rendu du jeu
void GameDraw(Player *player)
{
    LevelDraw();
    PlayerDraw(player);
    DrawEnemyPool(&enemyPool);
    DrawBulletPool(&playerBulletPool, player->position);
}

// Déchargement
void GameUnload(void)
{
    FreeBulletPool(&playerBulletPool);
    FreeEnemyPool(&enemyPool);
    CloseWindow();
}

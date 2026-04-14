#include "../../lib/core/GameManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/PlayerController.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/systems/EnemyPool.h"
#include "../../lib/systems/EnemySpawner.h"
#include "../../lib/systems/CollisionSystem.h"
#include "../../lib/systems/LifeManager.h"
#include "../../lib/systems/TriggerSystem.h"
#include "../../lib/core/RessourcesManager.h"
#include "../../lib/core/Camera.h"


// Initialise le jeu
void GameInit(Player *player)
{
    LevelInit();
    PlayerInit(player);

    //Init enemy
    InitEnemyPool(&enemyPool, 100);
    EnemySpawnerInit(&enemySpawner);
    InitBulletPool(&bulletPool, 3000);

    InitBulletPool(&playerBulletPool, 300);
}

// Mise a jour du jeu
void GameUpdate(Player *player, double* timeSpent, double* startReload)
{
    CameraUpdate(&camera, player);
    NextLvlUpdate(player, &enemyPool, &playerBulletPool, &enemySpawner);
    UpdateEnemySpawner(&enemySpawner, &enemyPool);
    UpdateEnemyPool(&enemyPool, getPlayerCenter(player));
    UpdateBulletPool(&bulletPool);

    CheckEnemyBulletCollision(&enemyPool, &playerBulletPool);

    PlayerUpdate(player, currentLevel.platforms, currentLevel.platformCount, timeSpent, startReload);
    //TriggerSystemUpdate(player, &currentLevel); Temporairement enlever et la map passe dans le système de vague
    UpdateBulletPool(&playerBulletPool);
}

// Rendu du jeu
void GameDraw(Player *player)
{
    ClearBackground(RAYWHITE);
    DrawTextureEx(*RM_GetTexture("../ressources/sprites/bgs/Nebula.png"), (Vector2){-300, 300}, 0.0f, 3.0f, WHITE);
    LevelDraw();
    PlayerDraw(player);
    DrawEnemyPool(&enemyPool);
    DrawBulletPool(&playerBulletPool, player->position);
    DrawBulletPool(&bulletPool, player->position);
}

// Décharger
void GameUnload(Player player)
{
    FreeBulletPool(&playerBulletPool);
    FreeEnemyPool(&enemyPool);
    FreeBuff(player.buff);

    CloseWindow();
}

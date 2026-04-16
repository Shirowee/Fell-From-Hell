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
#include "../../lib/menu/Screen.h"
#include <string.h>


// Initialise le jeu
void GameInit(Player *player)
{
    RM_LoadAll();
    LevelInit();
    PlayerInit(player);

    //Init enemy
    InitEnemyPool(&enemyPool, 100);
    EnemySpawnerInit(&enemySpawner);
    InitBulletPool(&bulletPool, 300);

    InitBulletPool(&playerBulletPool, 300);

    //init des touches
    int size = 0;
    unsigned char *data = LoadFileData("keybinds.dat", &size);

    if (data != NULL && size == sizeof(KeyBindings)) {
        memcpy(&keys, data, sizeof(KeyBindings));
        UnloadFileData(data);
    }
}

// Remet le jeu à zéro (après une mort)
void GameReset(Player *player) {
    int i;

    readJsonLvl("map1");
    LevelInit();

    PlayerInit(player);

    bulletPool.nbBulletsActive = 0;
    playerBulletPool.nbBulletsActive = 0;

    for (i = 0; i < enemyPool.capacity; i++)
        enemyPool.tab[i].active = 0;

    EnemySpawnerInit(&enemySpawner);

    for (i = 0; i < currentLevel.enemyCount; i++)
        currentLevel.enemies[i].spawned = false;

}

// Mise a jour du jeu
void GameUpdate(Player *player, double* timeSpent, double* startReload)
{
    CameraUpdate(&camera, player);
    NextLvlUpdate(player, &enemySpawner);
    UpdateEnemySpawner(&enemySpawner, &enemyPool);
    UpdateEnemyPool(&enemyPool, getPlayerCenter(player));
    EnemiesPositionFix(&enemyPool, currentLevel.platforms, currentLevel.platformCount);
    UpdateBulletPool(&bulletPool);

    CheckEnemyBulletCollision(&enemyPool, &playerBulletPool, &(player->weapon));
    CheckBulletsPlatformsCollision(&bulletPool, currentLevel.platforms, currentLevel.platformCount);

    PlayerUpdate(player, currentLevel.platforms, currentLevel.platformCount, timeSpent, startReload);
    //TriggerSystemUpdate(player, &currentLevel); Temporairement enlever et la map passe dans le système de vague
    UpdateBulletPool(&playerBulletPool);
    CheckBulletsPlatformsCollision(&playerBulletPool, currentLevel.platforms, currentLevel.platformCount);
}

// Rendu du jeu
void GameDraw(Player *player)
{
    ClearBackground(RAYWHITE);
    //DrawTextureEx(*RM_GetTexture("../ressources/sprites/bgs/Nebula.png"), (Vector2){-300, 300}, 0.0f, 3.0f, WHITE);
    //DrawTextureEx(*RM_GetTexture(TEX_BACKGROUND_NEBULA), (Vector2){-300, 300}, 0.0f, 3.0f, WHITE);
    LevelDraw();
    PlayerDraw(player);
    DrawEnemyPool(&enemyPool, player->position);
    DrawBulletPool(&playerBulletPool);
    DrawBulletPool(&bulletPool);
}

// Décharger
void GameUnload(Player player)
{
    FreeBulletPool(&playerBulletPool);
    FreeEnemyPool(&enemyPool);
    FreeBuff(player.buff);

    CloseWindow();
}

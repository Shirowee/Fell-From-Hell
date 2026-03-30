#ifndef ENEMYPOOL_H
#define ENEMYPOOL_H

#include "../../raylib/include/raylib.h"
#include "../enemies/EnemyController.h"




typedef struct {
    enemy_t* tab; //liste contenant les enemy
    int active; //booléen pour l'activité de la pool
    int capacity; //nombre d'elements
} enemyPool_t;

void InitEnemyPool(enemyPool_t* pool, int capacity);
void SpawnEnemyPool(enemyPool_t* pool, Vector2 pos, 
                    float speed, Vector2 size, int dmg, float bulletSpeed, int bulletSize);
void UpdateEnemyPool(enemyPool_t* pool, Vector2 playerPos);
void DrawEnemyPool(enemyPool_t* pool);
void FreeEnemyPool(enemyPool_t* pool);

extern enemyPool_t enemyPool;
#endif
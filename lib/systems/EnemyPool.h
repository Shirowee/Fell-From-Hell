/*#ifndef ENEMYPOOL_H
#define ENEMYPOOL_H

#include "../../raylib/include/raylib.h"
#include "../.h"

typedef enum {
    default
} enemy_t;

typedef struct {
    bullet_t* tab; //liste contenant les enemy
    int active; //booléen pour l'activité de la pool
    int capacity; //nombre d'elements

    enemy_t enemy_type;
} bulletPool_t;

void InitBulletPool(bulletPool_t* pool, int capacity);
void SpawnBulletPool(bulletPool_t* pool, Vector2 pos, int dir);
void UpdateBulletPool(bulletPool_t* pool);
void DrawBulletPool(bulletPool_t* pool);
void FreeBulletPool(bulletPool_t* pool);

extern bulletPool_t bulletPool;
#endif*/
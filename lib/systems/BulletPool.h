#ifndef BULLETPOOL_H
#define BULLETPOOL_H

#include "../../raylib/include/raylib.h"
#include "Projectiles.h"

typedef struct {
    bullet_t* tab; //liste contenant les bullets
    int active; //booléen pour l'activité de la pool
    int capacity; //nombre d'elements
} bulletPool_t;

void InitBulletPool(bulletPool_t* pool, int capacity);
void SpawnBulletPool(bulletPool_t* pool, Vector2 pos, int dir, int speed, int size, int dmg);
void UpdateBulletPool(bulletPool_t* pool);
void DrawBulletPool(bulletPool_t* pool);
void FreeBulletPool(bulletPool_t* pool);

extern bulletPool_t bulletPool;
extern bulletPool_t playerBulletPool;
#endif
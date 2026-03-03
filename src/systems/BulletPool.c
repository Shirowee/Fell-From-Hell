#include "../../raylib/include/raylib.h"
#include "../../lib/systems/BulletPool.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

bulletPool_t bulletPool; 

void InitBulletPool(bulletPool_t* pool, int capacity) {
    pool->active = 1;
    pool->capacity = capacity;
    pool->tab = malloc(sizeof(bullet_t) * capacity);

    for(int i = 0; i < capacity;i++){
        pool->tab[i].active = 0;
    }
}

void SpawnBulletPool(bulletPool_t* pool, Vector2 pos, int dir) {
    //on cherche la premiere bullet inactive (disponible)
    int spawned = 0;
    for(int i=0; (i < pool->capacity) && (spawned == 0); i++) {
        
        if (pool->tab[i].active == 0) {
            InitBullet(&pool->tab[i], 500, 10, 1, pos, dir);
            spawned = 1;
        }
    }
}

void UpdateBulletPool(bulletPool_t* pool) {
    for(int i=0; i < pool->capacity; i++) {
        UpdateBullet(&pool->tab[i]);
    }
}

void DrawBulletPool(bulletPool_t* pool) {
    for(int i=0; i < pool->capacity; i++) {
        DrawBullet(&pool->tab[i]);
    }
}

void FreeBulletPool(bulletPool_t* pool) {
    free(pool->tab);
    pool->tab = NULL;
    pool->capacity = 0;
}
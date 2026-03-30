#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "../../lib/systems/EnemyPool.h"

typedef struct {
    float timer;
    float cooldown;
} EnemySpawner;

void EnemySpawnerInit(EnemySpawner* spawner);
void SpawnRandomEnemy(enemyPool_t* pool);
void UpdateEnemySpawner(EnemySpawner* spawner, enemyPool_t* pool);

extern EnemySpawner enemySpawner;
#endif
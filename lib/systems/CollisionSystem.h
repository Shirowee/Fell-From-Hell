#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "EnemyPool.h"
#include "BulletPool.h"
#include "../player/Player.h"

void CheckEnemyBulletCollision(enemyPool_t* enemies, bulletPool_t* bullets);

void checkPlayerEnemyCollision(Player* player, enemyPool_t* enemies, int* total_dmg);

void checkPlayerBulletCollision(Player* player, bulletPool_t* bullets, int* total_dmg);

#endif
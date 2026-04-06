#ifndef ENEMY_STATES_H
#define ENEMY_STATES_H

#include "../../lib/enemies/EnemyController.h"
#include "../systems/BulletPool.h"

void EnemyState_Idle(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);
void EnemyState_MoveTowardsPlayer(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);
void EnemyState_MoveRandom(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);
void EnemyState_EnemyShootCircle(enemy_t* enemy, bulletPool_t* pool, Vector2 playerPos);


#endif
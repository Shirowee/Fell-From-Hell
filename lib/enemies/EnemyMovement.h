#include "../../lib/enemies/EnemyController.h"

#ifndef ENEMY_MOVEMENT_H
#define ENEMY_MOVEMENT_H

void EnemyMove(enemy_t * enemy);
void EnemyMoveTowardsPlayer(enemy_t * enemy, Vector2 player);

#endif

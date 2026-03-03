#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/enemies/EnemyController.h"
#include "../../raylib/include/raylib.h"

//Déplacements latéraux
void EnemyMove(enemy_t * enemy)
{
    float dt = GetFrameTime(); // Temps entre images
    enemy->enemyPos.x += enemy->enemySpeed * dt;
}


void EnemyShoots(enemy_t * enemy)
{
    enemy->isShooting = 1;
}
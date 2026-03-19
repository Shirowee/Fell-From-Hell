#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/enemies/EnemyController.h"
#include "../../raylib/include/raylib.h"

//Déplacements latéraux
void EnemyMove(enemy_t * enemy)
{
    float dt = GetFrameTime(); // Temps entre images
    enemy->pos.x += enemy->speed * dt;
}

void EnemyMoveTowardsPlayer(enemy_t * enemy, Vector2 player)
{
    float dt = GetFrameTime(); // Temps entre images
    int x_to_moove = player.x - enemy->pos.x;
    int y_to_moove = player.y - enemy->pos.y;
    if ( x_to_moove >= y_to_moove ) {
        enemy->pos.x += enemy->speed * dt;
        enemy->pos.y += enemy->speed/x_to_moove * dt;
    }
    else 
    {
        enemy->pos.x += enemy->speed/x_to_moove * dt;
        enemy->pos.y += enemy->speed * dt;
    }
}

#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/enemies/EnemyController.h"
#include "../../raylib/include/raylib.h"
#include <math.h>

//Déplacements latéraux
void EnemyMove(enemy_t * enemy)
{
    float dt = GetFrameTime(); // Temps entre images
    enemy->pos.x += enemy->speed * dt;
}

void EnemyMoveTowardsPlayer(enemy_t *enemy, Vector2 player)
{
    float dt = GetFrameTime();

    // Soustracion  
    Vector2 direction;
    direction.x = player.x - enemy->pos.x;
    direction.y = player.y - enemy->pos.y;

    // longueur vect
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.0f)
    {
        // Normalisation
        direction.x /= length;
        direction.y /= length;

        enemy->pos.x += direction.x * enemy->speed * dt;
        enemy->pos.y += direction.y * enemy->speed * dt;
    }
}
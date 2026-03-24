#include "../../raylib/include/raylib.h"
#include "../../lib/systems/CollisionSystem.h"
#include <math.h>

void CheckEnemyBulletCollision(enemyPool_t* enemies, bulletPool_t* bullets)
{
    for (int i = 0; i < enemies->capacity; i++)
    {
        enemy_t* e = &enemies->tab[i];
        if (!e->active) continue;

        for (int j = 0; j < bullets->capacity; j++)
        {
            bullet_t* b = &bullets->tab[j];
            if (!b->active) continue;

            float dx = e->pos.x - b->bulletPos.x;
            float dy = e->pos.y - b->bulletPos.y;

            float dist = sqrtf(dx * dx + dy * dy);

            if (dist < (e->size.x * 0.5f + b->bulletSize))
            {
                e->active = 0;
                b->active = 0;

                break;
            }
        }
    }
}
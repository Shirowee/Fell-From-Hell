#include "../../lib/enemies/EnemyController.h"
#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/systems/BulletPool.h"
#include "../../raylib/include/raylib.h"


//init l'ennemi
void EnemyInit(enemy_t * enemy, float speed, Vector2 size, int dmg,
                Vector2 pos, int bulletSpeed, int bulletSize) {
    enemy->speed = speed;
    enemy->pos = pos;
    enemy->dmg = dmg;
    enemy->isShooting = 0;
    enemy->size = size;
    enemy->dir = 0;
    enemy->bulletSpeed = bulletSpeed;
    enemy->bulletSize = bulletSize;
    enemy->active = 1;
}

//maj de la logique de l'ennemi
void EnemyUpdate(enemy_t * enemy)
{
    EnemyMove(enemy);
    if (enemy->isShooting == 1){
        enemy->isShooting = 0;
        SpawnBulletPool(&bulletPool,enemy->pos,enemy->dir,enemy->bulletSpeed,enemy->bulletSize,enemy->dmg);
    }
}


//dessine l'ennemi
void EnemyDraw(enemy_t * enemy)
{
    DrawRectangleV(enemy->pos, enemy->size, RED);
}

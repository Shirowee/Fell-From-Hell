#include "../../lib/enemies/EnemyController.h"
#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/systems/BulletPool.h"
#include "../../raylib/include/raylib.h"


//init l'ennemi
void EnemyInit(enemy_t * enemy)
{
    enemy->speed = 30;
    enemy->pos = (Vector2){ 100, 350 };
    enemy->dmg = 1;
    enemy->isShooting = 0;
    enemy->size = (Vector2){30,30};
    enemy->dir = 0;
    enemy->bulletSpeed = 200;
    enemy->bulletSize = 200;
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

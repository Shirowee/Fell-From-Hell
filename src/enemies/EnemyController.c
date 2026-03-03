#include "../../lib/enemies/EnemyController.h"
#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/systems/BulletPool.h"
#include "../../raylib/include/raylib.h"


//init l'ennemi
void EnemyInit(enemy_t * enemy)
{
    enemy->enemySpeed = 30;
    enemy->enemyPos = (Vector2){ 100, 350 };
    enemy->enemyDmg = 1;
    enemy->isShooting = 0;
    enemy->enemySize = (Vector2){30,30};
}

//maj de la logique de l'ennemi
void EnemyUpdate(enemy_t * enemy)
{
    EnemyMove(enemy);
    if (enemy->isShooting == 1){
        enemy->isShooting = 0;
        SpawnBulletPool(&bulletPool,enemy->enemyPos,40);
    }
}


//dessine l'ennemi
void EnemyDraw(enemy_t * enemy)
{
    DrawRectangleV(enemy->enemyPos, enemy->enemySize, RED);
}

/*
#include "../../lib/enemies/EnemyController.h"
#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/systems/BulletPool.h"
#include "../../raylib/include/raylib.h"

void EnemyState_Idle(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);
void EnemyState_Move(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);
void EnemyState_Attack(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);

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

    enemy->state = EnemyState_Idle;
}

//tir
void EnemyShoots(enemy_t * enemy)
{
    enemy->isShooting = 1;
}

/*
* STATES MACHINE
*/
void EnemyState_Idle(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos){
    enemy->stateTimer += GetFrameTime();

    if (enemy->stateTimer > 1.0f){
        enemy->state = EnemyState_Move;
        enemy->stateTimer = 0;
    }
}

void EnemyState_Move(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos){
    EnemyMoveTowardsPlayer(enemy, playerPos);
}

void EnemyState_Attack(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos){
    return;
}

//maj de la logique de l'ennemi
void EnemyUpdate(enemy_t * enemy, Vector2 playerPos)
{
    if ( enemy->active == 0 ) return;
    
    enemy->state(enemy,&bulletPool, playerPos);
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
*/
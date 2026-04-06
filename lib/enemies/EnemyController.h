#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include "../../raylib/include/raylib.h"
#include "../../lib/systems/BulletPool.h"

typedef enum {
    ENEMY_CHASER,
    ENEMY_SHOOTER,
} EnemyType;

typedef struct enemy_s {
    /*
    * Enemy informations
    */
    float speed; // vitesse
    Vector2 size; // taille
    int dmg; // dégats
    Vector2 pos; // position
    int dir; //direction
    int bulletSpeed; //vitesse bullet
    int bulletSize; //taille bullet

    /*
    * For the state machine
    */
    EnemyType type;
    void (*state)(struct enemy_s*, bulletPool_t*, Vector2);
    float stateTimer;

    /*
    * for the logic
    */
    int isShooting; //si elle doit être dessinée
    int active; //si l'enemi doit être affiché
} enemy_t;

void EnemyInit(enemy_t * enemy, float speed, Vector2 size, int dmg, Vector2 pos, int bulletSpeed, int bulletSize);
void EnemyUpdate(enemy_t * enemy, Vector2 playerPos);
void EnemyDraw(enemy_t * enemy);
void EnemyShoots(enemy_t * enemy);

void EnemyState_Idle(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);
void EnemyState_Move(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);
void EnemyState_Attack(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);

#endif

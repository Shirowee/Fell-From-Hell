#include "../../raylib/include/raylib.h"

#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

typedef struct enemy_s {
    float enemySpeed; // vitesse
    Vector2 enemySize; // taille
    int enemyDmg; // dégats
    Vector2 enemyPos; // position
    int isShooting; //si elle doit être dessinée
} enemy_t;

void EnemyInit(enemy_t * enemy);
void EnemyUpdate(enemy_t * enemy);
void EnemyDraw(enemy_t * enemy);

#endif

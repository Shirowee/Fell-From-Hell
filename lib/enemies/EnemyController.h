#include "../../raylib/include/raylib.h"

#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

typedef struct enemy_s {
    float speed; // vitesse
    Vector2 size; // taille
    int dmg; // dégats
    Vector2 pos; // position
    int isShooting; //si elle doit être dessinée
    int dir; //direction
    int bulletSpeed; //vitesse bullet
    int bulletSize; //taille bullet
} enemy_t;

void EnemyInit(enemy_t * enemy);
void EnemyUpdate(enemy_t * enemy);
void EnemyDraw(enemy_t * enemy);

#endif

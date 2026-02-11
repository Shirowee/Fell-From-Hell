#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "../../raylib/include/raylib.h"

typedef struct bullet_s {
    float bulletSpeed; // vitesse
    float bulletSize; // taille
    int bulletDmg; // dégats
    Vector2 bulletPos; // position
    int bulletDir; // direction
} bullet_t;

void BulletInit(bullet_t * bullet); 

void BulletUpdate(bullet_t * bullet);

void BulletDraw(bullet_t * bullet);

#endif

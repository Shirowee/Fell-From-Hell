#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "../../raylib/include/raylib.h"

typedef struct bullet_s {
    float bulletSpeed; // vitesse
    float bulletSize; // taille
    int bulletDmg; // dégats
    Vector2 bulletPos; // position
    int bulletDir; // direction en deg
    int active; //si elle doit être dessinée
} bullet_t;

void InitBullet(bullet_t * bullet, int speed, int size, int dmg, Vector2 Pos, int dir); 

void UpdateBullet(bullet_t * bullet);

void DrawBullet(bullet_t * bullet);

#endif

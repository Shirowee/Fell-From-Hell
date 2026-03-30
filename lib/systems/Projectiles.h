#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "../../raylib/include/raylib.h"

//differents type de bullet
#define BASIC 0
#define EXPLOSIF 1
#define RAYON 2
#define MELEE 3

typedef struct bullet_s {
    float bulletSpeed; // vitesse
    float bulletSize; // taille
    int bulletDmg; // dégats
    Vector2 bulletPos; // position
    int bulletDir; // direction en deg
    double createTime; //heure de creation
    float lifeTime; //durer de vie (pour bullet explosif et rayon)
    int indice; // indice (BASIC EXPLOSIF RAYON MELEE)
    int active; //si elle doit être dessinée
} bullet_t;

void InitBullet(bullet_t * bullet, int speed, int size, int dmg, Vector2 Pos, int dir, float lifeTime, int indice);

void UpdateBullet(bullet_t * bullet);

void DrawExplosion(bullet_t * bullet);

void DrawBullet(bullet_t * bullet, Vector2 posJoueur);

#endif

#ifndef BULLETPOOL_H
#define BULLETPOOL_H

#include "../../raylib/include/raylib.h"
#include "../../lib/enemies/Projectiles.h"

typedef struct {
    bullet_t* liste; //liste contenant les bullets
    int active; //booléen pour l'activité de la pool
    int number; //nombre d'elements
} BulletPool;



#endif
#include "../../lib/systems/BuffSystem.h"
#include "../../lib/player/PlayerController.h"
#include <stdlib.h>

buff_t* BuffInit(void){
    buff_t* buff = malloc(sizeof(buff_t));

    buff->dmg = 1;
    buff->fireRate = 1;
    buff->reloadTime = 1;
    buff->dispersion = 1;
    buff->bulletSpeed = 1;
    buff->bulletSize = 1;
    buff->movementSpeed = MAX_SPEED_X;
    buff->dashCooldown = 3;

    return(buff);
}

void FreeBuff(buff_t* buff){
    free(buff);
}

void Buff(buff_t* buff, float add, int indice){
    switch (indice){
        case 0 : BuffDmg(buff, add); break;
        case 1 : BufffireRate(buff, add); break;
        case 2 : BuffreloadTime(buff, add); break;
        case 3 : Buffdispersion(buff, add); break;
        case 4 : BuffbulletSpeed(buff, add); break;
        case 5 : BuffbulletSize(buff, add); break;
        case 6 : BuffmovementSpeed(buff, add); break;
        case 7 : BuffdashCooldown(buff, add); break;
        default: break;
    }
}
void BuffDmg(buff_t* buff, float add){
    buff->dmg += buff->dmg*add;
}
void BufffireRate(buff_t* buff, float add){
    buff->fireRate += buff->fireRate*add;
}
void BuffreloadTime(buff_t* buff, float sub){
    buff->reloadTime -= buff->reloadTime*sub;
}
void Buffdispersion(buff_t* buff, float sub){
    buff->dispersion -= buff->dispersion*sub;
}
void BuffbulletSpeed(buff_t* buff, float add){
    buff->bulletSpeed += buff->bulletSpeed*add;
}
void BuffbulletSize(buff_t* buff, float add){
    buff->bulletSize += buff->bulletSize*add;
}
void BuffmovementSpeed(buff_t* buff, float add){
    buff->movementSpeed += buff->movementSpeed*add;
}
void BuffdashCooldown(buff_t* buff, float sub){
    buff->dashCooldown -= buff->dashCooldown*sub;
}
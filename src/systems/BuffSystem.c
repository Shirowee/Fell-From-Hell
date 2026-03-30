#include "../../lib/systems/BuffSystem.h"
#include <stdlib.h>

buff_t* BuffInit(void){
    buff_t* buff = malloc(sizeof(buff_t));

    buff->dmg = 1;
    buff->fireRate = 1;
    buff->reloadTime = 1;
    buff->dispersion = 1;
    buff->bulletSpeed = 1;
    buff->bulletSize = 1;

    return(buff);
}

void FreeBuff(buff_t* buff){
    free(buff);
}

void BuffDmg(buff_t* buff, float add){
    buff->dmg += add;
}
void BufffireRate(buff_t* buff, float add){
    buff->fireRate += add;
}
void BuffreloadTime(buff_t* buff, float sub){
    buff->reloadTime -= sub;
}
void Buffdispersion(buff_t* buff, float sub){
    buff->dispersion -= sub;
}
void BuffbulletSpeed(buff_t* buff, float add){
    buff->bulletSpeed += add;
}
void BuffbulletSize(buff_t* buff, float add){
    buff->bulletSize += add;
}
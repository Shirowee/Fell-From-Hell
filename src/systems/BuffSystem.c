#include "../../lib/systems/BuffSystem.h"

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
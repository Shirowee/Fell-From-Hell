#ifndef BUFFSYSTEM_H
#define BUFFSYSTEM_H

#include "../../raylib/include/raylib.h"

typedef struct {
    //buff mineur
    float dmg;
    float fireRate;
    float reloadTime;
    float dispersion;
    float bulletSpeed;
    float bulletSize;

    /*
    effect_t effet;     //effet de l'arme
    float fireDmg;      //degats du feu
    float iceTime;      //durer du gel
    float movementSpeed;
    float dashCooldown;

    //buff majeur
    int extraDash;
    */
} buff_t;

buff_t* BuffInit(void);
void FreeBuff(buff_t* buff);
void BuffDmg(buff_t* buff, float add);
void BufffireRate(buff_t* buff, float add);
void BuffreloadTime(buff_t* buff, float sub);
void Buffdispersion(buff_t* buff, float sub);
void BuffbulletSpeed(buff_t* buff, float add);
void BuffbulletSize(buff_t* buff, float add);

#endif
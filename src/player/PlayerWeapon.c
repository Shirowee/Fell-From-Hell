#include "../../lib/player/PlayerWeapon.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>




weapon_t minigun ={0, 12.5, 10, 75, 75, 3, AUCUN, 20, 100, 500, 10};
weapon_t lance_flammes ={1, 10, 20, 300, 300, 3, FEU, 30, 20, 500, 10};
weapon_t lance_missile_tete_chercheuse ={2, 125, 2, 10, 10, 6, AUCUN, 0, 100, 500, 10};
weapon_t fusil_a_pompe ={3, 12.5, 0.75, 6, 6, 5, AUCUN, 50, 20, 400, 10};
weapon_t pistolet_laser ={4, 50, 0.8, 10, 10, 3, AUCUN, 0, 100, 500, 10};
weapon_t fusil_rafales ={5, 35, 2, 11, 11, 3, AUCUN, 10, 100, 500, 10};
weapon_t lance_glace ={6, 10, 20, 300, 300, 3, GEL, 30, 20, 500, 10};
weapon_t lance_roquette ={7, 150, 0.8, 8, 8, 4, FEU, 0, 50, 500, 10};
weapon_t epee_longue ={8, 75, 1.5, -1, -1, -1, AUCUN, 160, 10, 500, 10};
weapon_t sniper ={9, 150, 0.75, 6, 6, 3, AUCUN, 0, 100, 1200, 15};
weapon_t arbalete ={10, 70, 1, 8, 6, 3, TOUS, 0, 100, 500, 10};
weapon_t pistolet_eclectique ={11, 35, 2, 15, 15, 2, ELECTRIQUE, 40, 50, 500, 10};
weapon_t pistolet_mitrailleur ={12, 10, 10, 40, 40, 0.5, AUCUN, 25, 50, 500, 10};
weapon_t pistolet_multi_direction ={13, 20, 2, 20, 20, 1.5, AUCUN, 7.5, 100, 500, 10};


void PlayerShoot(weapon_t * weapon, Vector2 posJoueur, double  * timeSpent, double * startReload){
    
    int gamepad = 0;
    float direction;
    float cooldown = 1/weapon->tps; //temps entre deux tir
    Vector2 posSouris; 

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetTime()- *timeSpent >= cooldown && !IsReloading(weapon, startReload)){
        posSouris = GetMousePosition();
        direction = ((int)(atan2(posSouris.y - posJoueur.y, posSouris.x - posJoueur.x) * 180 / PI) + 360) % 360;
        spawnBulletWeapon(*weapon, posJoueur, direction);
        *timeSpent = GetTime();
        (weapon->amo_left)--;
    }

    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2) && GetTime()- *timeSpent >= cooldown && !IsReloading(weapon, startReload)){
        float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
        float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
        direction = atan2(rightStickY, rightStickX) * 180/PI;
        spawnBulletWeapon(*weapon, posJoueur, direction);
        *timeSpent = GetTime();
        (weapon->amo_left)--;
    }
}

int IsReloading(weapon_t * weapon, double * startReload){
    if(weapon->amo_left == 0){
        *startReload = GetTime();
        weapon->amo_left = weapon->magazine;
    }
    if(weapon->amo_left == weapon->magazine && GetTime()- *startReload < weapon->reloadTime){
        return(1);
    }
    return(0);
}

void ChangeWeapon(weapon_t * oldWeapon, weapon_t newWeapon){
    *oldWeapon = newWeapon;
}
    
#define MINIGUN 0
#define LANCE_FLAMEMS 1
#define LANCE_MISSILE_TETE_CHERCHEUSE 2
#define FUSIL_A_POMPE 3
#define PISTOLET_LASER 4
#define FUSIL_RAFALES 5
#define LANCE_GLACE 6
#define LANCE_ROQUETTE 7
#define EPEE_LONGUE 8
#define SNIPER 9
#define ARBALETE 10
#define PISTOLET_ELECTRIQUE 11
#define PISTOLET_MITRAILLEUR 12
#define PISTOLET_MULTI_DIRECTION 13

void spawnBulletWeapon(weapon_t weapon, Vector2 posJoueur, int direction){
    
    switch(weapon.indice){
        case FUSIL_A_POMPE : SpawnBulletPool(&playerBulletPool, posJoueur, direction, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + weapon.dispersion/6, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 2*(weapon.dispersion/6), weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 3*(weapon.dispersion/6), weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction - weapon.dispersion/6, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction - 2*(weapon.dispersion/6), weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction - 3*(weapon.dispersion/6), weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            break;

        case PISTOLET_MULTI_DIRECTION : direction += rand() % weapon.dispersion - weapon.dispersion/2;
            SpawnBulletPool(&playerBulletPool, posJoueur, direction, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 90, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 180, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 270, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
            break;


        default : if(weapon.dispersion != 0) direction += rand() % weapon.dispersion - weapon.dispersion/2; // calcul de la dispesion
            SpawnBulletPool(&playerBulletPool, posJoueur, direction, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg);
    }
}
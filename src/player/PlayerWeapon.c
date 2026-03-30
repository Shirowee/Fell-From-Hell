#include "../../lib/player/Player.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


weapon_t minigun ={0, 12.5, 10, 75, 75, 3, AUCUN, 30, 100, 500, 15};
weapon_t lance_flammes ={1, 10, 20, 300, 300, 3, FEU, 30, 0.5, 500, 30};
weapon_t lance_missile_tete_chercheuse ={2, 125, 2, 10, 10, 6, AUCUN, 0, 4, 500, 10};
weapon_t fusil_a_pompe ={3, 12.5, 0.75, 6, 6, 5, AUCUN, 50, 0.75, 400, 10};
weapon_t pistolet_laser ={4, 50, 0.8, 10, 10, 3, AUCUN, 0, 1, 500, 50};
weapon_t fusil_rafales ={5, 35, 2, 11, 11, 3, AUCUN, 10, 100, 500, 10};
weapon_t lance_glace ={6, 10, 20, 300, 300, 3, GEL, 30, 0.5, 500, 10};
weapon_t lance_roquette ={7, 150, 0.8, 8, 8, 4, FEU, 0, 0.5, 500, 10};
weapon_t epee_longue ={8, 75, 1.5, -1, -1, -1, AUCUN, 160, 10, 500, 10};
weapon_t sniper ={9, 150, 0.75, 6, 6, 3, AUCUN, 0, 100, 1200, 20};
weapon_t arbalete ={10, 70, 1, 8, 6, 3, TOUS, 0, 100, 500, 10};
weapon_t pistolet_eclectique ={11, 35, 2, 15, 15, 2, ELECTRIQUE, 40, 50, 500, 10};
weapon_t pistolet_mitrailleur ={12, 10, 10, 40, 40, 0.5, AUCUN, 25, 50, 500, 10};
weapon_t pistolet_multi_direction ={13, 20, 2, 20, 20, 1.5, AUCUN, 7.5, 100, 500, 10};


void PlayerShoot(Player* player, double  * timeSpent, double * startReload){
    int gamepad = 0;
    float direction;
    weapon_t* weapon = &(player->weapon);
    Vector2 posJoueur = player->position; 
    Vector2 posSouris; 

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsReloading(weapon, startReload) && Cooldown(*weapon, timeSpent)){
        posSouris = GetMousePosition();
        direction = ((int)(atan2(posSouris.y - posJoueur.y, posSouris.x - posJoueur.x) * 180 / PI) + 360) % 360;
        spawnBulletWeapon(*weapon, posJoueur, direction);
        (weapon->amo_left)--;
    }

    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2) && Cooldown(*weapon, timeSpent) && !IsReloading(weapon, startReload)){
        float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
        float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
        direction = atan2(rightStickY, rightStickX) * 180/PI;
        spawnBulletWeapon(*weapon, posJoueur, direction);
        (weapon->amo_left)--;
    }
}

int Cooldown(weapon_t weapon, double  * timeSpent){
    float cooldown = 1/weapon.tps; //temps entre deux tir
    if (GetTime() - *timeSpent >= cooldown){
        *timeSpent = GetTime();
        return 1;
    }
    return 0;
}


int IsReloading(weapon_t * weapon, double * startReload){
    if(weapon->amo_left == 0){
        *startReload = GetTime();
        weapon->amo_left = weapon->magazine;
    }
    if(weapon->amo_left == weapon->magazine && GetTime() - *startReload < weapon->reloadTime) 
        return 1;
    return 0;
}

void ChangeWeapon(weapon_t * oldWeapon, weapon_t newWeapon){
    *oldWeapon = newWeapon;
}

void spawnBulletWeapon(weapon_t weapon, Vector2 posJoueur, int direction){
    
    switch(weapon.indice){
        case FUSIL_A_POMPE : 
            SpawnBulletPool(&playerBulletPool, posJoueur, direction, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + weapon.dispersion/6, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 2*(weapon.dispersion/6), weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 3*(weapon.dispersion/6), weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction - weapon.dispersion/6, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction - 2*(weapon.dispersion/6), weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction - 3*(weapon.dispersion/6), weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            break;

        case PISTOLET_LASER : 
            SpawnBulletPool(&playerBulletPool, posJoueur, direction, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, RAYON);
            break;

        case LANCE_ROQUETTE : 
            SpawnBulletPool(&playerBulletPool, posJoueur, direction, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, EXPLOSIF);
            break;

        case PISTOLET_MULTI_DIRECTION : 
            direction += GetRandomValue(weapon.dispersion /-2, weapon.dispersion /2);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 90, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 180, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, posJoueur, direction + 270, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
            break;


        default : 
            if(weapon.dispersion != 0) direction += GetRandomValue(weapon.dispersion /-2, weapon.dispersion /2); // calcul de la dispesion
            SpawnBulletPool(&playerBulletPool, posJoueur, direction, weapon.bulletSpeed, weapon.bulletSize, weapon.dmg, weapon.lifeTime, BASIC);
    }
}
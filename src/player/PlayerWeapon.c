#include "../../lib/player/Player.h"
#include "../../lib/core/GameManager.h"
#include "../../lib/menu/Screen.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


weapon_t minigun ={0, 12.5, 10, 75, 75, 3, AUCUN, 30, 100, 900, 15};
weapon_t lance_flammes ={1, 10, 20, 300, 300, 3, FEU, 30, 0.5, 900, 30};
weapon_t lance_missile_tete_chercheuse ={2, 125, 2, 10, 10, 6, AUCUN, 0, 4, 900, 10};
weapon_t fusil_a_pompe ={3, 12.5, 0.75, 6, 6, 5, AUCUN, 50, 0.75, 700, 10};
weapon_t pistolet_laser ={4, 50, 0.8, 10, 10, 3, AUCUN, 0, 1, 900, 50};
weapon_t fusil_rafales ={5, 35, 2, 11, 11, 3, AUCUN, 10, 100, 900, 10};
weapon_t lance_glace ={6, 10, 20, 300, 300, 3, GEL, 30, 0.5, 900, 10};
weapon_t lance_roquette ={7, 150, 0.8, 8, 8, 4, FEU, 0, 0.5, 900, 15};
weapon_t epee_longue ={8, 75, 1.5, -1, -1, -1, AUCUN, 160, 10, 900, 10};
weapon_t sniper ={9, 150, 0.75, 6, 6, 3, AUCUN, 0, 100, 1500, 20};
weapon_t arbalete ={10, 70, 1, 8, 6, 3, TOUS, 0, 100, 800, 10};
weapon_t pistolet_eclectique ={11, 35, 2, 15, 15, 2, ELECTRIQUE, 40, 50, 900, 10};
weapon_t pistolet_mitrailleur ={12, 10, 10, 40, 40, 0.5, AUCUN, 25, 50, 900, 10};
weapon_t pistolet_multi_direction ={13, 20, 2, 20, 20, 1.5, AUCUN, 7.5, 100, 900, 10};


void PlayerShoot(Player* player, double  * timeSpent, double * startReload){
    
    int gamepad = 0;
    float direction;
    weapon_t* weapon = &(player->weapon);
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsReloading(weapon, startReload) && Cooldown(*weapon, timeSpent)){
        direction = (atan2(mouseWorld.y - getPlayerCenter(player).y, mouseWorld.x - getPlayerCenter(player).x) * 180 / PI);
        spawnBulletWeapon(*weapon, *player, direction);
        (weapon->amo_left)--;
    }

    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2) && !IsReloading(weapon, startReload) && Cooldown(*weapon, timeSpent)){
        float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
        float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
        direction = atan2(rightStickY, rightStickX) * 180/PI;
        spawnBulletWeapon(*weapon, *player, direction);
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

void ChangeWeapon(weapon_t * oldWeapon, int indice){
    switch (indice){
        case MINIGUN : *oldWeapon = minigun; break;
        case LANCE_FLAMMES : *oldWeapon = lance_flammes; break;
        case LANCE_MISSILE_TETE_CHERCHEUSE : *oldWeapon = lance_missile_tete_chercheuse; break;
        case FUSIL_A_POMPE : *oldWeapon = fusil_a_pompe; break;
        case PISTOLET_LASER : *oldWeapon = pistolet_laser; break;
        case FUSIL_RAFALES : *oldWeapon = fusil_rafales; break;
        case LANCE_GLACE : *oldWeapon = lance_glace; break;
        case LANCE_ROQUETTE : *oldWeapon = lance_roquette; break;
        case EPEE_LONGUE : *oldWeapon = epee_longue; break;
        case SNIPER : *oldWeapon = sniper; break;
        case ARBALETE : *oldWeapon = arbalete; break;
        case PISTOLET_ELECTRIQUE : *oldWeapon = pistolet_eclectique; break;
        case PISTOLET_MITRAILLEUR : *oldWeapon = pistolet_mitrailleur; break;
        case PISTOLET_MULTI_DIRECTION : *oldWeapon = pistolet_multi_direction; break;
        default: break;
    }
}

void spawnBulletWeapon(weapon_t weapon, Player player, int direction){
    
    switch(weapon.indice){
        case FUSIL_A_POMPE : 
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction + weapon.dispersion * player.buff->dispersion /6, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction + 2*(weapon.dispersion * player.buff->dispersion /6), weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction + 3*(weapon.dispersion * player.buff->dispersion /6), weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction - weapon.dispersion * player.buff->dispersion /6, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction - 2*(weapon.dispersion * player.buff->dispersion /6), weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction - 3*(weapon.dispersion * player.buff->dispersion /6), weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            break;

        case PISTOLET_LASER : 
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, RAYON);
            break;

        case LANCE_ROQUETTE : 
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, EXPLOSIF);
            break;

        case PISTOLET_MULTI_DIRECTION : 
            direction += GetRandomValue(weapon.dispersion * player.buff->dispersion /-2, weapon.dispersion * player.buff->dispersion /2);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction + 90, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction + 180, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction + 270, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
            break;


        default : 
            if(weapon.dispersion != 0) direction += GetRandomValue(weapon.dispersion * player.buff->dispersion /-2, weapon.dispersion * player.buff->dispersion /2); // calcul de la dispesion
            SpawnBulletPool(&playerBulletPool, getPlayerCenter(&player), direction, weapon.bulletSpeed * player.buff->bulletSpeed, weapon.bulletSize * player.buff->bulletSize, weapon.dmg * player.buff->dmg, weapon.lifeTime, BASIC);
    }
}
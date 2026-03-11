#include "../../lib/player/PlayerWeapon.h"
#include <math.h>

weapon_t minigun ={12.5, 10, 75, 3, AUCUN, 20, 100};
weapon_t lance_flammes ={10, 20, 300, 3, FEU, 30, 20};
weapon_t lance_missile_tete_chercheuse ={125, 2, 10, 6, AUCUN, 0, 100};
weapon_t fusil_a_pompe ={12.5, 0.5, 6, 5, AUCUN, 50, 20};
weapon_t pistolet_laser ={50, 0.8, 10, 3, AUCUN, 0, 100};
weapon_t fusil_rafales ={35, 2, 11, 3, AUCUN, 10, 100};
weapon_t lance_glace ={10, 20, 300, 3, GEL, 30, 20};
weapon_t lance_roquette ={150, 0.8, 8, 4, FEU, 0, 50};
weapon_t epee_longue ={75, 1.5, -1, -1, AUCUN, 160, 10};
weapon_t sniper ={150, 0.5, 6, 3, AUCUN, 0, 100};
weapon_t arbalete ={70, 1, 8, 3, TOUS, 0, 100};
weapon_t pistolet_eclectique ={35, 2, 15, 2, ELECTRIQUE, 40, 50};
weapon_t pistolet_mitrailleur ={10, 10, 40, 0.5, AUCUN, 25, 50};
weapon_t pistolet_jsp_koi ={20, 2, 20, 1.5, AUCUN, 7.5, 100};


void PlayerShoot(weapon_t weapon, Vector2 posJoueur, double  * time){
    int gamepad = 0;
    float direction;
    float cooldown = 1/weapon.tps; //temps entre deux tir
    Vector2 posSouris; 

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetTime()- *time >= cooldown){
        posSouris = GetMousePosition();
        direction = ((int)(atan2(posSouris.y - posJoueur.y, posSouris.x - posJoueur.x) * 180 / PI) + 360) % 360;
        SpawnBulletPool(&playerBulletPool, posJoueur, direction); 
        *time = GetTime();
    }

    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2) && GetTime()- *time >= cooldown){
        float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
        float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
        direction = atan2(rightStickY, rightStickX) * 180/PI;
        SpawnBulletPool(&playerBulletPool, posJoueur, direction);
        *time = GetTime();
    }
}

void ChangeWeapon(weapon_t * oldWeapon, weapon_t newWeapon){
    *oldWeapon = newWeapon;
}
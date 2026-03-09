#include "../lib/player/PlayerWeapon.h"
#include "../lib/systems/BulletPool.h"
#include <stdio.h>
#include <math.h>

int main(){
    InitWindow(800, 450, "Weapon Test");

    bulletPool_t playerBulletPool;
    InitBulletPool(&playerBulletPool, 300);

    weapon_t weapon = minigun; //fusil_a_pompe
    int gamepad = 0;
    float direction;
    float cooldown = 1/weapon.tps; //temps entre deux tir
    double time=0;
    Vector2 posJoueur = (Vector2){400, 200};
    Vector2 posSouris; 

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //update
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetTime()-time >= cooldown){
            posSouris = GetMousePosition();
            direction = (int)(atan2(posJoueur.x * posSouris.y - posJoueur.y * posSouris.x, posJoueur.x * posSouris.x + posJoueur.y * posSouris.y) * 180/PI + 360) % 360;
            SpawnBulletPool(&playerBulletPool, posJoueur, direction); 
            time = GetTime();
        }

        if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2) && GetTime()-time >= cooldown){
            float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
            float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
            direction = atan2(rightStickY, rightStickX) * 180/PI;
            SpawnBulletPool(&playerBulletPool, posJoueur, direction);
            time = GetTime();
        }

        UpdateBulletPool(&playerBulletPool);


        //draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBulletPool(&playerBulletPool);

        DrawFPS(10, 10);
        
        EndDrawing();
    }

    FreeBulletPool(&playerBulletPool);
    CloseWindow();
    return 0;
}

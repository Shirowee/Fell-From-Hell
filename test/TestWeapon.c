#include "../lib/player/PlayerWeapon.h"
#include <stdio.h>

int main(){
    InitWindow(800, 450, "Weapon Test");

    //bulletPool_t playerBulletPool;
    InitBulletPool(&playerBulletPool, 300);

    weapon_t weapon = minigun;
    int gamepad = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //update
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            SpawnBulletPool(&playerBulletPool, (Vector2){400, 200}, 0); 

        if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)){
            //float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
            //float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
            SpawnBulletPool(&playerBulletPool, (Vector2){400, 200}, 0);
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

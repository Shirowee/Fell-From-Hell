#include "../lib/player/PlayerWeapon.h"
#include "../lib/systems/BulletPool.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    InitWindow(800, 450, "Weapon Test");

    //init pour rand ; faudra mettre dans gameInit
    srand(time(NULL));

    
    InitBulletPool(&playerBulletPool, 300);

    weapon_t weapon = minigun; //fusil_a_pompe
    Vector2 posJoueur =(Vector2){400, 200};
    double timeSpent=0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //update
        PlayerShoot(weapon, posJoueur, &timeSpent);
        if (IsKeyDown(KEY_RIGHT)){
            ChangeWeapon(&weapon, epee_longue);
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

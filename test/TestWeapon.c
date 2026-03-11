#include "../lib/player/PlayerWeapon.h"
#include "../lib/systems/BulletPool.h"
#include <stdio.h>


int main(){
    InitWindow(800, 450, "Weapon Test");

    
    InitBulletPool(&playerBulletPool, 300);

    weapon_t weapon = minigun; //fusil_a_pompe
    Vector2 posJoueur =(Vector2){400, 200};
    double time=0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //update
        PlayerShoot(weapon, posJoueur, &time);
        /*
        if (IsKeyDown(SPACE)){
            ChangeWeapon(&weapon, fusil_a_pompe);
        }
            */

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

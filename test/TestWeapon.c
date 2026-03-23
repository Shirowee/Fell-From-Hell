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
    double timeSpent=0; //temp entre deux tir
    double startReload = -10;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //update
        PlayerShoot(&weapon, posJoueur, &timeSpent, &startReload);
        if (IsKeyDown(KEY_RIGHT)){
            ChangeWeapon(&weapon, lance_flammes); //lance_flammes fusil_a_pompe pistolet_laser lance_glace lance_roquette sniper arbalete pistolet_mitrailleur pistolet_multi_direction 
        }

        UpdateBulletPool(&playerBulletPool);


        //draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Arme équipée : %d", weapon.indice), 10, 30, 20, DARKGRAY);
        DrawText(TextFormat("amo left : %d", weapon.amo_left), 10, 50, 20, DARKGRAY);
        DrawBulletPool(&playerBulletPool);

        DrawFPS(10, 10);
        
        EndDrawing();
    }

    FreeBulletPool(&playerBulletPool);
    CloseWindow();
    return 0;
}

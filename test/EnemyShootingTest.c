#include "../raylib/include/raylib.h"
#include "../lib/enemies/EnemyController.h"
#include "../lib/enemies/EnemyMovement.h"
#include "../../lib/systems/BulletPool.h"
#include<stdio.h>
int main(void)
{
    InitWindow(800, 450, "Enemy Test");
    enemy_t enemy;
    EnemyInit(&enemy,30,(Vector2){20,30},1,(Vector2){200,200},500,10);
    InitBulletPool(&bulletPool,300);


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        
        if (IsKeyPressed(KEY_SPACE)){
            EnemyShoots(&enemy);
        
        }
        
        EnemyUpdate(&enemy);
        UpdateBulletPool(&bulletPool);



        BeginDrawing();
        ClearBackground(RAYWHITE);
        EnemyDraw(&enemy);
        DrawBulletPool(&bulletPool);

        DrawFPS(10, 10);
        
        EndDrawing();
    }

    FreeBulletPool(&bulletPool);
    CloseWindow();
    return 0;
}

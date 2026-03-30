#include "../raylib/include/raylib.h"
#include "../../lib/systems/EnemyPool.h"
#include "../../lib/systems/BulletPool.h"
#include<stdio.h>

int main(void)
{
    InitWindow(800, 450, "Enemy Pool Test");
    InitEnemyPool(&enemyPool,200);
    InitBulletPool(&bulletPool,300);


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        
        if (IsKeyPressed(KEY_SPACE)){
            SpawnEnemyPool(&enemyPool,(Vector2){200,200},30,(Vector2){20,30},1,500,10);
            
        }
        
        UpdateEnemyPool(&enemyPool,(Vector2){0,0});
        UpdateBulletPool(&bulletPool);



        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawEnemyPool(&enemyPool);
        DrawBulletPool(&bulletPool);

        DrawFPS(10, 10);
        
        EndDrawing();
    }
    FreeEnemyPool(&enemyPool);
    FreeBulletPool(&bulletPool);
    CloseWindow();
    return 0;
}

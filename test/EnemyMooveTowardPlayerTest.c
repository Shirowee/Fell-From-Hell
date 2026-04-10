#include "../raylib/include/raylib.h"
#include "../../lib/systems/EnemyPool.h"
#include "../../lib/systems/BulletPool.h"
#include "../../lib/enemies/EnemyMovement.h"
#include<stdio.h>

Camera2D camera = { 0 };

int main(void)
{
    InitWindow(1920, 1080, "Enemy Pool Shooting Test");

    /*
    InitEnemyPool(&enemyPool,200);
    Vector2 playerPos = (Vector2){800,450};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        
        if (IsKeyPressed(KEY_SPACE)){
            SpawnEnemyPool(&enemyPool,(Vector2){200,200},180,(Vector2){20,30},1,500,10);
        }
        

        playerPos = GetMousePosition();


        UpdateEnemyPool(&enemyPool,playerPos);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawEnemyPool(&enemyPool);
        DrawBulletPool(&bulletPool);

        DrawFPS(10, 10);
        
        EndDrawing();
    }
    FreeEnemyPool(&enemyPool);
    CloseWindow();
    */
    return 0;
}

#include "../raylib/include/raylib.h"
#include "../lib/enemies/BulletPool.h"
int main(void)
{
    InitWindow(800, 450, "BulletPool Test");

    bulletPool_t enemyBullets;
    InitBulletPool(&enemyBullets, 300);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
            SpawnBulletPool(&enemyBullets, (Vector2){400, 200}, 0); 

        UpdateBulletPool(&enemyBullets);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBulletPool(&enemyBullets);

        DrawFPS(10, 10);
        
        EndDrawing();
    }

    FreeBulletPool(&enemyBullets);
    CloseWindow();
    return 0;
}

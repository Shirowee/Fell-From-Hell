#include "../raylib/include/raylib.h"
#include "../lib/systems/BulletPool.h"
int main(void)
{
    InitWindow(800, 450, "BulletPool Test");

    //--------------------------ADD TO GAME INIT-------------------
    InitBulletPool(&bulletPool, 300);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
            SpawnBulletPool(&bulletPool, (Vector2){400, 200}, 0, 20, 5, 1); 

        UpdateBulletPool(&bulletPool);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBulletPool(&bulletPool);

        DrawFPS(10, 10);
        
        EndDrawing();
    }

    FreeBulletPool(&bulletPool);
    CloseWindow();
    return 0;
}

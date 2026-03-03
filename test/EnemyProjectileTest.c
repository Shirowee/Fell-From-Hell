#include "../raylib/include/raylib.h"
#include "../lib/systems/Projectiles.h"
int main(void)
{
    InitWindow(800, 450, "Enemy Projectile Test");

    bullet_t bullet;
    InitBullet(&bullet, 20, 10, 10, (Vector2){400, 200}, 0);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        UpdateBullet(&bullet);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBullet(&bullet);

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

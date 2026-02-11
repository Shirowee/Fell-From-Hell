#include "../raylib/include/raylib.h"
#include "../../lib/enemies/EnemyProjectiles.h"
int main(void)
{
    InitWindow(800, 450, "Enemy Projectile Test");

    bullet_t bullet;
    BulletInit(&bullet);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BulletUpdate(&bullet);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BulletDraw(&bullet);

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

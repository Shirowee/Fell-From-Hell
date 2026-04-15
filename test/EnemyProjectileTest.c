#include "../raylib/include/raylib.h"
#include "../lib/systems/BulletPool.h"
#include "../lib/menu/Screen.h"

Camera2D camera = { 0 };
KeyBindings keys = { KEY_A, KEY_D, KEY_SPACE, KEY_E };

int main(void)
{
    InitWindow(800, 450, "Enemy Projectile Test");

    InitBulletPool(&bulletPool, 300);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
            SpawnBulletPool(&bulletPool, (Vector2){400, 200}, 0, 20, 10, 10, 100, BASIC);

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

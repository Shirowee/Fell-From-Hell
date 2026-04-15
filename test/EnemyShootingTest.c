#include "../raylib/include/raylib.h"
#include "../lib/enemies/EnemyController.h"
#include "../lib/enemies/EnemyMovement.h"
#include "../lib/systems/BulletPool.h"
#include "../lib/menu/Screen.h"

Camera2D camera = { 0 };
KeyBindings keys = { KEY_A, KEY_D, KEY_SPACE, KEY_E };

int main(void)
{
    InitWindow(800, 450, "Enemy Shooting Test");

    enemy_t enemy;
    EnemyInit(&enemy, 100, 30, (Vector2){20, 30}, 1, (Vector2){200, 200}, 500, 10, ENEMY_SHOOTER);
    InitBulletPool(&bulletPool, 3000);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
            EnemyShoots(&enemy);

        EnemyUpdate(&enemy, (Vector2){0, 0});
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

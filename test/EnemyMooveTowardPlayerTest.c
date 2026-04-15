#include "../raylib/include/raylib.h"
#include "../lib/systems/EnemyPool.h"
#include "../lib/systems/BulletPool.h"
#include "../lib/menu/Screen.h"

Camera2D camera = { 0 };
KeyBindings keys = { KEY_A, KEY_D, KEY_SPACE, KEY_E };

int main(void)
{
    InitWindow(1920, 1080, "Enemy Move Toward Player Test");

    InitEnemyPool(&enemyPool, 200);
    InitBulletPool(&bulletPool, 3000);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
            SpawnEnemyPool(&enemyPool, (Vector2){200, 200}, 100, 180, (Vector2){20, 30}, 1, 500, 10, ENEMY_CHASER);

        UpdateEnemyPool(&enemyPool, GetMousePosition());

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

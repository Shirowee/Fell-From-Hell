#include "../raylib/include/raylib.h"
#include "../lib/player/PlayerController.h"
#include "../lib/player/PlayerWeapon.h"
#include "../lib/systems/BulletPool.h"
#include "../lib/menu/Screen.h"
#include <stdlib.h>
#include <time.h>

Camera2D camera = { 0 };
KeyBindings keys = { KEY_A, KEY_D, KEY_SPACE, KEY_E };

int main(void)
{
    InitWindow(800, 450, "Weapon Test");

    srand(time(NULL));

    Player player;
    PlayerInit(&player);
    InitBulletPool(&playerBulletPool, 300);

    double timeSpent = 0;
    double startReload = -10;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        PlayerShoot(&player, &timeSpent, &startReload);

        if (IsKeyDown(KEY_RIGHT))
            ChangeWeapon(&player.weapon, LANCE_FLAMMES);

        UpdateBulletPool(&playerBulletPool);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Arme equipee : %d", player.weapon.indice), 10, 30, 20, DARKGRAY);
        DrawText(TextFormat("amo left : %d", player.weapon.amo_left), 10, 50, 20, DARKGRAY);
        DrawBulletPool(&playerBulletPool);

        DrawFPS(10, 10);

        EndDrawing();
    }

    FreeBulletPool(&playerBulletPool);
    CloseWindow();

    return 0;
}

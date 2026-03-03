#include "../raylib/include/raylib.h"
#include "../lib/player/Player.h"
#include "../lib/core/GameManager.h"

// Point d'entrée du jeu
int main(void)
{
    InitWindow(800, 450, "Fell From Hell");

    Player player;

    GameInit(&player); // Initialisation du jeu

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        

        GameUpdate(&player); // Logique

        BeginDrawing();
        DrawFPS(10, 10);
        ClearBackground(RAYWHITE);

        GameDraw(&player);   // Dessin

        EndDrawing();
    }

    GameUnload(); // Nettoyage

    CloseWindow();
    return 0;
}

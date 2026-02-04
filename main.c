#include "raylib.h"
#include "core/GameManager.h"

// Point d'entrée du jeu
int main(void)
{
    InitWindow(800, 450, "Platformer Proto - Architecture");

    GameInit(); // Initialisation du jeu

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        GameUpdate(); // Logique

        BeginDrawing();
        ClearBackground(RAYWHITE);

        GameDraw();   // Dessin

        EndDrawing();
    }

    GameUnload(); // Nettoyage

    CloseWindow();
    return 0;
}

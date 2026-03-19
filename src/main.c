#include "../raylib/include/raylib.h"
#include "../lib/player/Player.h"
#include "../lib/core/GameManager.h"
#include "../lib/levels/LevelManager.h"

#define REF_LARGEUR 1920
#define REF_HAUTEUR 1080

// Point d'entrée du jeu
int main(void)
{
    if (!readJsonLvl("map1")) return -1;

    
    InitWindow(0, 0, "Fell From Hell");
    SetTargetFPS(60);

    float dynamicTileSize = (float)GetScreenHeight() / REF_HAUTEUR;

    Player player;
    GameInit(&player,dynamicTileSize); // Initialisation du jeu

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        float cameraSpeed = 800.0f * GetFrameTime(); 
        if (IsKeyDown(KEY_UP)) camera.target.y -= cameraSpeed;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += cameraSpeed;

        GameUpdate(&player); // Logique

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            BeginMode2D(camera);
                GameDraw(&player);   // Dessin
            EndMode2D();

            DrawFPS(10, 10);
        EndDrawing();
    }

    GameUnload(); // Nettoyage

    CloseWindow();
    return 0;
}

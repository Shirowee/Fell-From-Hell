#include "../raylib/include/raylib.h"
#include "../lib/player/Player.h"
#include "../lib/core/GameManager.h"
#include "../lib/levels/LevelManager.h"

#define REF_LARGEUR 1920
#define REF_HAUTEUR 1080

bool verifPremPlan(bool onTop){
    if (IsWindowFocused() && !onTop) {
        SetWindowState(FLAG_WINDOW_TOPMOST);
            onTop = true;
        } 
        else if (!IsWindowFocused() && onTop) {
            ClearWindowState(FLAG_WINDOW_TOPMOST);
            onTop = false;
    }
    return onTop;
}

// Point d'entrée du jeu
int main(void)
{
    ChangeDirectory(GetApplicationDirectory()); // Ce place au niveau du .exe pour éviter des prob avec le readJson après
    if (!readJsonLvl("map1")) return -1; // Si impossible de lire la map

    bool isTopmost = false; // Variable Etat de la fenêtre (Premier Plan ou Non)
    
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_HIDDEN); // Ouverture de la fenêtre sans la barre et caché (pour ne pas rendre le redimensionnement)

    InitWindow(850, 400, "Fell From Hell");
    
    int monitor = GetCurrentMonitor(); // Récupère l'écran où est affiché le jeu
    int screenWidth = GetMonitorWidth(monitor) - 1; // Récupère la dimension de l'écran
    int screenHeight = GetMonitorHeight(monitor);

    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(0, 0);
    ClearWindowState(FLAG_WINDOW_HIDDEN);


    float dynamicTileSize = (float)GetScreenHeight() / REF_HAUTEUR;

    Player player;
    GameInit(&player,dynamicTileSize); // Initialisation du jeu

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        isTopmost = verifPremPlan(isTopmost);
        float cameraSpeed = 800.0f * GetFrameTime(); //TEMPORAIRE POUR FAIRE LA MAP
        if (IsKeyDown(KEY_UP)) camera.target.y -= cameraSpeed; //TEMPORAIRE POUR FAIRE LA MAP
        if (IsKeyDown(KEY_DOWN)) camera.target.y += cameraSpeed; //TEMPORAIRE POUR FAIRE LA MAP

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

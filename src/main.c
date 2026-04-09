#include "../raylib/include/raylib.h"
#include "../lib/player/Player.h"
#include "../lib/core/GameManager.h"
#include "../lib/core/WindowManager.h"
#include "../lib/core/ResolutionManager.h"
#include "../lib/levels/LevelManager.h"
#include "../lib/systems/LifeManager.h"


// Point d'entrée du jeu
int main(void) {
    /*************************
    * INITIALISATION SYSTEME *
    *************************/
    ChangeDirectory(GetApplicationDirectory()); // Ce place au niveau du .exe pour éviter des prob avec le readJson après
    if (!readJsonLvl("map2")) return -1; // Si impossible de lire la map

    WindowInit(); // Initialisation de la fenêtre
    ResolutionInit(currentLevel.info.width, currentLevel.info.height); // Initialise tout ce qui est lié a la résolution

    /************************
    * INITIALISATION DU JEU *
    ************************/
    Player player;
    double timeSpent=0; //temp entre deux tir
    double startReload = -10;
    GameInit(&player); // Initialisation du jeu

    Camera2D camera = { 0 };
    camera.offset = (Vector2){ 0, 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.zoom   = resolution.scale;

    /********************
    * BOUCLE PRINCIPALE *
    ********************/
    while (!WindowShouldClose())
    {
        WindowManager_Update(); // Update de l'état de la fenêtre

        float cameraSpeed = 800.0f * GetFrameTime(); // TEMPORAIRE MAP
        if(IsKeyDown(KEY_UP)) camera.target.y -= cameraSpeed; // TEMPORAIRE MAP
        if(IsKeyDown(KEY_DOWN)) camera.target.y += cameraSpeed; // TEMPORAIRE MAP
        if(IsKeyDown(KEY_U)) camera.target.x += cameraSpeed; // TEMPORAIRE MAP
        if(IsKeyDown(KEY_Y)) camera.target.x -= cameraSpeed; // TEMPORAIRE MAP

        // LOGIQUE
        GameUpdate(&player, &timeSpent, &startReload);

        // DESSIN
        BeginDrawing();
               

            BeginMode2D(camera);     
                GameDraw(&player);
            EndMode2D();

            DrawFPS(10, 10);
            HPDraw(&player, 10, 50, 300, 20);
            
        EndDrawing();
    }

    /*********
    * UNLOAD *
    *********/
    GameUnload(); 

    return 0;
}

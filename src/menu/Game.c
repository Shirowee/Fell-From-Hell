#include "../../raylib/include/raylib.h"
#include "../../lib/player/Player.h"
#include "../../lib/core/GameManager.h"
#include "../../lib/core/WindowManager.h"
#include "../../lib/core/Screen.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/core/ResolutionManager.h"
#include "../../lib/systems/LifeManager.h"

#define REF_LARGEUR 1920
#define REF_HAUTEUR 1080


// Point d'entrée du jeu
Screen_t Game(Player* player, Camera2D* camera)
{

    /************************
    * INITIALISATION DU JEU
    *************************/
    double timeSpent=0; //temp entre deux tir
    double startReload = -10;

    /*******************
    * BOUCLE PRINCIPALE
    ********************/
    while (!IsKeyPressed(KEY_ESCAPE) && !IsKeyPressed(KEY_L))
    {
        WindowManager_Update(); // Update de l'état de la fenêtre

        float cameraSpeed = 800.0f * GetFrameTime(); // TEMPORAIRE MAP
        if(IsKeyDown(KEY_UP)) camera->target.y -= cameraSpeed; // TEMPORAIRE MAP
        if(IsKeyDown(KEY_DOWN)) camera->target.y += cameraSpeed; // TEMPORAIRE MAP
        if(IsKeyDown(KEY_U)) camera->target.x += cameraSpeed; // TEMPORAIRE MAP
        if(IsKeyDown(KEY_Y)) camera->target.x -= cameraSpeed; // TEMPORAIRE MAP

        // LOGIQUE
        GameUpdate(player, &timeSpent, &startReload);

        // DESSIN
        BeginDrawing();
            ClearBackground(RAYWHITE);         
            GameDraw(player);
            
            DrawFPS(10, 10);
        EndDrawing();
    }

    if(IsKeyPressed(KEY_ESCAPE))
        return (SCREEN_PAUSE);
        
    return (SCREEN_END_LEVEL);
}
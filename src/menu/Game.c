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

Camera2D camera = { 0 };

// Point d'entrée du jeu
Screen_t Game(Player* player)
Screen_t Game(Player* player)
{

    /************************
    * INITIALISATION DU JEU
    *************************/
    double timeSpent=0; //temp entre deux tir
    double startReload = -10;
    int monitorHeight = GetMonitorHeight(0);

    /*******************
    * BOUCLE PRINCIPALE
    ********************/
    while (!IsKeyPressed(KEY_ESCAPE) && !IsKeyPressed(KEY_L))
    {
        WindowManager_Update(); // Update de l'état de la fenêtre

        camera.target.y = player->position.y + player->size.y - monitorHeight/3;

        // LOGIQUE
        GameUpdate(player, &timeSpent, &startReload);

        // DESSIN
        BeginDrawing();
            ClearBackground(RAYWHITE);   
            BeginMode2D(camera);
                GameDraw(player);
            EndMode2D();

            ClearBackground(RAYWHITE);   
            BeginMode2D(camera);
                GameDraw(player);
            EndMode2D();

            DrawFPS(10, 10);
            HPDraw(player, 10, 30, (int)(GetScreenWidth() * 0.2f), (int)(GetScreenHeight() * 0.03f));
        EndDrawing();
    }

    if(IsKeyPressed(KEY_ESCAPE))
        return (SCREEN_PAUSE);
        
    NewLevel(1);
    return (SCREEN_END_LEVEL);
}
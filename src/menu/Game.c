#include "../../raylib/include/raylib.h"
#include "../../lib/player/Player.h"
#include "../../lib/core/GameManager.h"
#include "../../lib/core/WindowManager.h"
#include "../../lib/core/Screen.h"
#include "../../lib/levels/LevelManager.h"

#define REF_LARGEUR 1920
#define REF_HAUTEUR 1080


// Point d'entrée du jeu
Screen_t Game(Player* player)
{

    /************************
    * INITIALISATION DU JEU
    *************************/
    double timeSpent=0; //temp entre deux tir
    double startReload = -10;

    /*******************
    * BOUCLE PRINCIPALE
    ********************/
    while (!IsKeyPressed(KEY_ESCAPE))
    {
        WindowManager_Update(); // Update de l'état de la fenêtre

        // LOGIQUE
        GameUpdate(player, &timeSpent, &startReload);

        // DESSIN
        BeginDrawing();
            ClearBackground(RAYWHITE);         
            GameDraw(player);
            
            DrawFPS(10, 10);
        EndDrawing();
    }

    return (SCREEN_PAUSE);
}
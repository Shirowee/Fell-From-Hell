#include "../raylib/include/raylib.h"
#include "../lib/player/Player.h"
#include "../lib/core/GameManager.h"
#include "../lib/core/WindowManager.h"
#include "../lib/levels/LevelManager.h"
#include "../lib/systems/LifeManager.h"

#define REF_LARGEUR 1920
#define REF_HAUTEUR 1080


// Point d'entrée du jeu
int main(void)
{

    /****************
    * INITIALISATION SYSTEME
    *****************/
    ChangeDirectory(GetApplicationDirectory()); // Ce place au niveau du .exe pour éviter des prob avec le readJson après
    if (!readJsonLvl("map1")) return -1; // Si impossible de lire la map

    WindowInit(); // Initialisation de la fenêtre


    /************************
    * INITIALISATION DU JEU
    *************************/
    float dynamicTileSize = (float)GetScreenHeight() / REF_HAUTEUR;
    Player player;
    double timeSpent=0; //temp entre deux tir
    double startReload = -10;
    GameInit(&player,dynamicTileSize); // Initialisation du jeu


    /*******************
    * BOUCLE PRINCIPALE
    ********************/
    while (!WindowShouldClose() && isAlive(&player))
    {
        WindowManager_Update(); // Update de l'état de la fenêtre

        // LOGIQUE
        GameUpdate(&player, &timeSpent, &startReload);

        // DESSIN
        BeginDrawing();
            ClearBackground(RAYWHITE);         
            GameDraw(&player);
            HPDraw(&player, 20, 60, 400, 20);
            DrawText(TextFormat("HP = %i", player.stats.hp), 20, 90, 30, GREEN);
            DrawText(TextFormat("regenTimeOut = %f", player.stats.regenTimeOut), 20, 110, 30, ORANGE);
            
            DrawFPS(10, 10);
        EndDrawing();
    }

    if(!isAlive(&player)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("GAME OVER", 200, 200, 100, RED);
        EndDrawing();
        WaitTime(5);
    }

    /********
    * UNLOAD
    *********/
    GameUnload(); 

    return 0;
}

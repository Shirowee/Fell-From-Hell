#include "../raylib/include/raylib.h"
#include "../lib/player/Player.h"
#include "../lib/core/GameManager.h"
#include "../lib/core/WindowManager.h"
#include "../lib/levels/LevelManager.h"

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
    while (!WindowShouldClose())
    {
        WindowManager_Update(); // Update de l'état de la fenêtre

        // LOGIQUE
        GameUpdate(&player, &timeSpent, &startReload);

        // DESSIN
        BeginDrawing();
            ClearBackground(RAYWHITE);         
            GameDraw(&player);
            
            DrawFPS(10, 10);
        EndDrawing();
    }

    /********
    * UNLOAD
    *********/
    GameUnload(); 

    return 0;
}

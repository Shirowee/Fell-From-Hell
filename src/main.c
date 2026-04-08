#include "../raylib/include/raylib.h"
#include "../lib/player/Player.h"
#include "../lib/core/GameManager.h"
#include "../lib/core/WindowManager.h"
#include "../lib/core/Screen.h"
#include "../lib/levels/LevelManager.h"

#define REF_LARGEUR 1920
#define REF_HAUTEUR 1080

// Point d'entrée du jeu
int main(void)
{
    
    WindowInit();
    Screen_t currentScreen = SCREEN_MENU;
    Screen_t previousScreen = SCREEN_MENU;
    /****************
    * INITIALISATION SYSTEME
    *****************/
    ChangeDirectory(GetApplicationDirectory()); // Ce place au niveau du .exe pour éviter des prob avec le readJson après
    if (!readJsonLvl("map1")) return -1; // Si impossible de lire la map


    /************************
    * INITIALISATION DU JEU
    *************************/
    float dynamicTileSize = (float)GetScreenHeight() / REF_HAUTEUR;
    Player player;
    GameInit(&player,dynamicTileSize); // Initialisation du jeu
    

    while (!WindowShouldClose() && currentScreen != SCREEN_EXIT) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        
        switch(currentScreen) {
            case SCREEN_MENU: 
                currentScreen = MenuUpdate(); 
                previousScreen = SCREEN_MENU;
                break;
            case SCREEN_GAME: 
                currentScreen = Game(&player); break;
            case SCREEN_SETTINGS: 
                currentScreen = SettingsUpdate(previousScreen); break;
            case SCREEN_PAUSE: 
                currentScreen = PauseUpdate(); 
                previousScreen = SCREEN_PAUSE;
                break;
            case SCREEN_END_LEVEL: 
                currentScreen = EndLevelUpdate(); break;
            default: break;
        }

        EndDrawing();
    }

    /********
    * UNLOAD
    *********/
    GameUnload(player); 

    return 0;
}

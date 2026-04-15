#include "../raylib/include/raylib.h"
#include "../lib/player/Player.h"
#include "../lib/core/GameManager.h"
#include "../lib/core/WindowManager.h"
#include "../lib/menu/Screen.h"
#include "../lib/core/ResolutionManager.h"
#include "../lib/core/ResolutionManager.h"
#include "../lib/levels/LevelManager.h"
#include "../lib/systems/LifeManager.h"

// Point d'entrée du jeu
int main(void)
{
    

    WindowInit();
    Screen_t currentScreen = SCREEN_MENU;
    Screen_t previousScreen = SCREEN_MENU;

    int screenWidth = GetScreenWidth();
    int screenHeigth = GetScreenHeight();

    /****************
    * INITIALISATION SYSTEME
    *****************/
    ChangeDirectory(GetApplicationDirectory()); // Ce place au niveau du .exe pour éviter des prob avec le readJson après
    if (!readJsonLvl("map1")) return -1; // Si impossible de lire la map

    ResolutionInit(currentLevel.info.width, screenWidth, screenHeigth); // Initialise tout ce qui est lié a la résolution

    /************************
    * INITIALISATION DU JEU *
    ************************/
    Player player;
    GameInit(&player); // Initialisation du jeu
    
    camera.offset = (Vector2){ 0, 0 };
    camera.target = (Vector2){ 0, player.position.y };
    camera.zoom   = resolution.scale;


    /********************
    * BOUCLE PRINCIPALE *
    ********************/
    while (!WindowShouldClose() && currentScreen != SCREEN_EXIT)
    {
        WindowManager_Update(); // Update de l'état de la fenêtre


        // DESSIN
        BeginDrawing();

        ClearBackground((Color){0, 7, 38, 0});

        switch(currentScreen) {
            case SCREEN_MENU:
                currentScreen = MenuUpdate(&player);
                previousScreen = SCREEN_MENU;
                break;
            case SCREEN_GAME: 
                currentScreen = Game(&player); break;
            case SCREEN_SETTINGS: 
                currentScreen = SettingsUpdate(previousScreen); break;
            case SCREEN_KEYBINDING: 
                currentScreen = KeybindingUpdate(); break;
            case SCREEN_SOUND: 
                currentScreen = SoundUpdate(); break;
            case SCREEN_PAUSE: 
                currentScreen = PauseUpdate(); 
                previousScreen = SCREEN_PAUSE;
                break;
            case SCREEN_END_GAME:
                currentScreen = DeathScreen(&player); break;
            case SCREEN_END_LEVEL: 
                currentScreen = EndLevelUpdate(&player); break;
            default: break;
        }

        EndDrawing();
    }


    /*********
    * UNLOAD *
    *********/
    GameUnload(player); 

    return 0;
}

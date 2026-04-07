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

    while (!WindowShouldClose() && currentScreen != SCREEN_EXIT) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch(currentScreen) {
            case SCREEN_MENU: 
                currentScreen = MenuUpdate(); break;
            case SCREEN_GAME: 
                currentScreen = Game(); break;
            case SCREEN_SETTINGS: 
                currentScreen = SettingsUpdate(); break;
            default: break;
        }

        EndDrawing();
    }

    return 0;
}

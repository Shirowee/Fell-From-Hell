#include "../../raylib/include/raylib.h"
#include "../../lib/menu/Screen.h"
#include "../../lib/core/RessourcesManager.h"

Screen_t SettingsUpdate(Screen_t previousScreen)
{
    static int selected = 0; // 0 = key_binding, 1 = sound, 2 = Exit

    const char *options[3] = {
        "CHANGEMENT DES TOUCHES",
        "CHANGEMENT DU SON",
        "REVENIR AU MENU"
    };
    if (previousScreen == SCREEN_PAUSE) {
        options[2] = "REVENIR AU MENU PAUSE";
    }

    int optionCount = 3;

    // Navigation clavier
    if (IsKeyPressed(KEY_DOWN)) {
        RM_PlaySound(SND_SELECT); // Joue un son de sélection
        selected++;
        if (selected >= optionCount) selected = 0;
    }

    if (IsKeyPressed(KEY_UP)) {
        RM_PlaySound(SND_SELECT); // Joue un son de sélection
        selected--;
        if (selected < 0) selected = optionCount - 1;
    }

    // Validation
    if (IsKeyPressed(KEY_ENTER)) {
        RM_PlaySound(SND_SELECTED); // Joue un son de sélectionné
        switch (selected) {
            case 0: return SCREEN_KEYBINDING; 
            case 1: return SCREEN_SOUND;
            case 2: if(previousScreen == SCREEN_MENU) return SCREEN_MENU;
            return SCREEN_PAUSE;
        }
    }

    // Affichage
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DrawText("PARAMETRES", screenWidth / 2 - 100, 150, 50, BLACK);

    for (int i = 0; i < optionCount; i++) {
        Color color = (i == selected) ? RED : DARKGRAY;

        DrawText(
            options[i],
            screenWidth / 2 - 100,
            300 + i * 80,
            30,
            color
        );
    }

    DrawText("Utilise les flèches et ENTREE", screenWidth / 2 - 150, screenHeight - 100, 20, GRAY);

    return SCREEN_SETTINGS;
}
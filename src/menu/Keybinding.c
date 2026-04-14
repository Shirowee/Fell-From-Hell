#include "../../raylib/include/raylib.h"
#include "../../lib/core/Screen.h"

Screen_t KeybindingUpdate()
{
    static int selected = 0; // 0 = key_binding, 1 = jsp_temp, 2 = Exit

    const char *options[3] = {
        "la tu met le texte",
        "BLABLA",
        "REVENIR AU MENU PARAMETRE"
    };
    

    int optionCount = 3;    //pense à changer la valeur si t'ajoute des option

    // Navigation clavier
    if (IsKeyPressed(KEY_DOWN)) {
        selected++;
        if (selected >= optionCount) selected = 0;
    }

    if (IsKeyPressed(KEY_UP)) {
        selected--;
        if (selected < 0) selected = optionCount - 1;
    }

    // Validation
    if (IsKeyPressed(KEY_ENTER)) {
        switch (selected) {
            case 0: /*la tu met se que ça fait*/ break;      
            case 1: /*la tu met se que ça fait*/ break;      
            case 2: return SCREEN_SETTINGS;
        }
    }

    // Affichage
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DrawText("Titre de la page", screenWidth / 2 - 100, 150, 50, BLACK); //la fo mettre le titre

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

    return SCREEN_KEYBINDING;
}
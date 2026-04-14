#include "../../raylib/include/raylib.h"
#include "../../lib/menu/Screen.h"
#include "../../lib/core/GameManager.h"

Screen_t DeathScreen(Player *player)
{
    static int selected = 0;
    
    const char *options[3] = {
        "Retour au menu principal",
        "Quitter"
    };
    
    int optionCount = 2;

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
            case 0: GameReset(player); return SCREEN_MENU;
            case 1: return SCREEN_EXIT; break;
        }
    }

    // Affichage
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DrawText("GAME OVER", screenWidth / 2 - 100, 150, 50, BLACK); 

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

    return SCREEN_END_GAME;
}
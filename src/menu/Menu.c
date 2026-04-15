#include "../../raylib/include/raylib.h"
#include "../../lib/menu/Screen.h"
#include "../../lib/core/RessourcesManager.h"
#include "../../lib/core/SavingManager.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/player/Player.h"
#include "../../lib/core/GameManager.h"

Screen_t MenuUpdate(Player *player)
{
    static int selected = 0; // 0 = Play, 1 = Settings, 2 = Exit

    const char *options[3] = {
        "JOUER",
        "PARAMETRES",
        "QUITTER LE JEU"
    };

    const char *optionSave[4] = {
        "JOUER",
        "CONTINUER",
        "PARAMETRES",
        "QUITTER LE JEU"
    };


    int optionCount = HasSaveFile() ? 4 : 3;

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
        if(optionCount == 4){
            switch (selected) {
                case 0: return SCREEN_GAME;
                case 1: GameReset(player); LoadGame(player); return SCREEN_GAME;
                case 2: return SCREEN_SETTINGS;
                case 3: return SCREEN_EXIT;
            }
        }

        switch (selected) {
            case 0: return SCREEN_GAME;
            case 1: return SCREEN_SETTINGS;
            case 2: return SCREEN_EXIT;
        }
    }

    // Affichage
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    /*============= Draw the title =============*/
    //DrawText("Fell From Hell", screenWidth / 2 - 100, 150, 50, BLACK);
    Texture2D tex = *RM_GetTexture("../ressources/sprites/others/Title.jpg");

    float scale = 7.0f;

    Vector2 position = {
        screenWidth / 2.0f - (tex.width * scale) / 2.0f + 200,
        screenHeight / 2.0f - (tex.height * scale) / 2.0f
    };

    DrawTextureEx(tex, position, 0.0f, scale, WHITE);

    
    for (int i = 0; i < optionCount; i++) {
        Color color = (i == selected) ? RED : (Color){240, 240, 240, 255};

        DrawText(
            (optionCount == 4 ? optionSave[i] : options[i]),
            100,
            400 + i * 80,
            30,
            color
        );
    }

    DrawText("Utilise les flèches et ENTREE", screenWidth / 2 - 150, screenHeight - 100, 20, GRAY);

    return SCREEN_MENU;
}
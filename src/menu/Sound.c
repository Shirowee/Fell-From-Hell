#include "../../raylib/include/raylib.h"
#include "../../lib/menu/Screen.h"
//#include "../../lib/core/RessourcesManager.h"

Screen_t SoundUpdate()
{
    static int selected = 0;        // 0 = musique, 1 = SFX, 2 = retour
    static float musicVolume = 1.0f;
    static float sfxVolume   = 1.0f;
    //static int initialized   = 0;

    //if (!initialized) {
    //    musicVolume = RM_GetMusicVolume();
    //    sfxVolume   = RM_GetSFXVolume();
    //    initialized = 1;
    //}

    const char *options[3] = {
        "MUSIQUE",
        "EFFETS SONORES",
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

    // Ajustement des sliders avec gauche/droite
    float step = 0.05f;
    if (selected == 0) {
        if (IsKeyPressed(KEY_RIGHT)) {
            musicVolume += step;
            if (musicVolume > 1.0f) musicVolume = 1.0f;
            //RM_SetMusicVolume(musicVolume);
        }
        if (IsKeyPressed(KEY_LEFT)) {
            musicVolume -= step;
            if (musicVolume < 0.0f) musicVolume = 0.0f;
            //RM_SetMusicVolume(musicVolume);
        }
    }
    if (selected == 1) {
        if (IsKeyPressed(KEY_RIGHT)) {
            sfxVolume += step;
            if (sfxVolume > 1.0f) sfxVolume = 1.0f;
            //RM_SetSFXVolume(sfxVolume);
        }
        if (IsKeyPressed(KEY_LEFT)) {
            sfxVolume -= step;
            if (sfxVolume < 0.0f) sfxVolume = 0.0f;
            //RM_SetSFXVolume(sfxVolume);
        }
    }

    // Validation
    if (IsKeyPressed(KEY_ENTER)) {
        switch (selected) {
            case 0: break;
            case 1: break;
            case 2: return SCREEN_SETTINGS;
        }
    }

    // Affichage
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int barWidth = 200;
    int barHeight = 20;
    int barX = screenWidth / 2 + 100;

    DrawText("SON", screenWidth / 2 - 40, 150, 50, BLACK);

    for (int i = 0; i < optionCount; i++) {
        Color color = (i == selected) ? RED : DARKGRAY;
        int y = 300 + i * 80;

        DrawText(options[i], screenWidth / 2 - 250, y, 30, color);

        // Slider pour musique et SFX
        if (i == 0 || i == 1) {
            float vol = (i == 0) ? musicVolume : sfxVolume;
            DrawRectangle(barX, y + 5, barWidth, barHeight, LIGHTGRAY);
            DrawRectangle(barX, y + 5, (int)(vol * barWidth), barHeight, color);
            DrawRectangleLines(barX, y + 5, barWidth, barHeight, GRAY);
            DrawText(TextFormat("%d%%", (int)(vol * 100)), barX + barWidth + 10, y + 5, 20, color);
        }
    }

    DrawText("Utilise les fleches et ENTREE", screenWidth / 2 - 150, screenHeight - 100, 20, GRAY);

    return SCREEN_SOUND;
}

#include "../../raylib/include/raylib.h"
#include "../../lib/menu/Screen.h"
#include <stdio.h>

KeyBindings keys = { KEY_A, KEY_D, KEY_SPACE, KEY_E};   //KEY_A correspond à la touche Q

Screen_t KeybindingUpdate()
{
    static int selected = 0;
    static int waitingKey = -1; // -1 = pas en attente

    const char *labels[5] = {
        "Gauche",
        "Droite",
        "Sauter",
        "Dash",
        "REVENIR"
    };

    int *keyValues[4] = {
        &keys.left,
        &keys.right,
        &keys.jump,
        &keys.dash
    };

    int optionCount = 5;

    // Navigation
    if (waitingKey == -1) {
        if (IsKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % optionCount;
        }
        if (IsKeyPressed(KEY_UP)) {
            selected = (selected - 1 + optionCount) % optionCount;
        }
    }

    // Sélection
    if (IsKeyPressed(KEY_ENTER)) {
        if (selected == optionCount-1) {
            SaveKeys();
            return SCREEN_SETTINGS;
        }
        waitingKey = selected; // on attend une nouvelle touche
    }

    // Attribution d'une touche
    if (waitingKey != -1) {
        int key = GetKeyPressed();
        if (key != 0 && key != 257){    // key == 0 pas de touche appuyée, key == 257 touche entrée
            *keyValues[waitingKey] = key;
            waitingKey = -1;
        }
    }

    // Affichage
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DrawText("Keybindings", screenWidth / 2 - 100, 150, 50, BLACK);

    for (int i = 0; i < optionCount; i++) {
        Color color = (i == selected) ? RED : DARKGRAY;

        char buffer[100];

        if (i < optionCount-1) {
            sprintf(buffer, "%s : %d", labels[i], *keyValues[i]);
        } else {
            sprintf(buffer, "%s", labels[i]);
        }

        if (waitingKey == i) {
            sprintf(buffer, "%s : ...", labels[i]);
        }

        DrawText(buffer, screenWidth / 2 - 150, 300 + i * 60, 30, color);
    }

    DrawText("ENTREE pour modifier", screenWidth / 2 - 150, screenHeight - 100, 20, GRAY);

    return SCREEN_KEYBINDING;
}

void SaveKeys() {
    FILE *file = fopen("save/keybinds.dat", "wb");
    if (file) {
        printf("jsp save truc\n");
        fwrite(&keys, sizeof(KeyBindings), 1, file);
        fclose(file);
    }
}

void LoadKeys() {
    FILE *file = fopen("save/keybinds.dat", "rb");
    if (file) {
        fread(&keys, sizeof(KeyBindings), 1, file);
        fclose(file);
    }
}
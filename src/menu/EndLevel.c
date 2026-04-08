#include "../../raylib/include/raylib.h"
#include "../../lib/core/Screen.h"
#include "../../lib/systems/BuffSystem.h"
#include "../../lib/player/PlayerWeapon.h"

Screen_t EndLevelUpdate(Player* player)
{
    static int selected = 0; // 0 = Buff 1, 1 = Buff 2, 2 = Buff 3, 3 = new weapon

    //choix de 3 buff aléatoire
    static int buff1 = -1;
    static int buff2;
    static int buff3;

    if(buff1 == -1){
        buff1 = GetRandomValue(0, 5); // 0 = dmg, 1 = fireRate, 2 = reloadTime, 3 = dispersion, 4 = bulletSpeed, 5 = bulletSize
        do{
            buff2 = GetRandomValue(0, 5);
        }while (buff2 == buff1);
        do{
            buff3 = GetRandomValue(0, 5);
        }while (buff3 == buff1 || buff3 == buff2);
    }
    


    //choix d'une arme aléatoire
    static int indiceWeapon = -1; 
    if(indiceWeapon == -1){
        do{
            indiceWeapon = GetRandomValue(0, 13); //indice voir PlayerWeapon
        }while (indiceWeapon == player->weapon.indice);
    }
    
    const char *options[7] = {
        "+10%% de dégats",
        "+10%% de cadence de tir",
        "-10%% de temps de rechargement",
        "-10%% de dispersion",
        "+10%% de la vitesse de la balle",
        "+10%% de la taille de la balle",
        "NOUVELLE ARME"
    };

    int optionCount = 4;

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
            case 0: Buff(player->buff, 0.1, buff1); break;
            case 1: Buff(player->buff, 0.1, buff2); break;
            case 2: Buff(player->buff, 0.1, buff3); break;
            case 3: ChangeWeapon(&(player->weapon), indiceWeapon); break;
        }
        return SCREEN_GAME;
    }

    // Affichage
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DrawText("Fin du niveau", screenWidth / 2 - 100, 150, 50, BLACK);

    Color color = (0 == selected) ? RED : DARKGRAY;
    DrawText(options[buff1], screenWidth / 2 - 100, 300, 30, color);
    color = (1 == selected) ? RED : DARKGRAY;
    DrawText(options[buff2], screenWidth / 2 - 100, 300 + 80, 30, color);
    color = (2 == selected) ? RED : DARKGRAY;
    DrawText(options[buff3], screenWidth / 2 - 100, 300 + 160, 30, color);
    color = (3 == selected) ? RED : DARKGRAY;
    DrawText(options[6], screenWidth / 2 - 100, 300 + 240, 30, color);

    DrawText("Utilise les flèches et ENTREE", screenWidth / 2 - 150, screenHeight - 100, 20, GRAY);

    return SCREEN_END_LEVEL;
}

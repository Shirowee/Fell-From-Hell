#include "../../raylib/include/raylib.h"
#include <stdio.h>

static bool isTopmost = false; 

void verifPremPlan(void){
    if (IsWindowFocused() && !isTopmost) {
        SetWindowState(FLAG_WINDOW_TOPMOST);
            isTopmost = true;
        } 
        else if (!IsWindowFocused() && isTopmost) {
            ClearWindowState(FLAG_WINDOW_TOPMOST);
            isTopmost = false;
    }
}

void WindowInit(){
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_HIDDEN); // Ouverture de la fenêtre sans la barre et caché (pour ne pas rendre le redimensionnement)

    InitWindow(850, 400, "Fell From Hell");
    
    #if defined(_WIN32) || defined(_WIN64) /* GESTION DE LA FENÊTRE POUR WINDOWS */
        int monitor = GetCurrentMonitor(); // Récupère l'écran où est affiché le jeu
        int screenWidth = GetMonitorWidth(monitor) - 1; // Récupère la dimension de l'écran
        int screenHeight = GetMonitorHeight(monitor);

        SetWindowSize(screenWidth, screenHeight);
        SetWindowPosition(0, 0);
    
    #else /* GESTION DE LA FENÊTRE POUR AUTRE QUE WINDOWS*/
        ToggleFullscreen();
    #endif

    ClearWindowState(FLAG_WINDOW_HIDDEN);
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
}

void WindowManager_Update(void) {
    verifPremPlan();
}


// Fonction pour permettre de connaître l'état de la fenêtre
bool WindowManager_IsTopmost(void) {
    return isTopmost;
}
    

#include "../../raylib/include/raylib.h"

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
    
    int monitor = GetCurrentMonitor(); // Récupere l'écran où est affiché le jeu
    int screenWidth = GetMonitorWidth(monitor) - 1; // Récupère la dimension de l'écran
    int screenHeight = GetMonitorHeight(monitor);

    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(0, 0);
    ClearWindowState(FLAG_WINDOW_HIDDEN);

    SetTargetFPS(60);
}

void WindowManager_Update(void) {
    verifPremPlan();
}

// Fonction pour permettre de connaître l'état de la fenêtre
bool WindowManager_IsTopmost(void) {
    return isTopmost;
}
    
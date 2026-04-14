#include "../../raylib/include/raylib.h"
#include "../../lib/player/Player.h"
#include "../../lib/core/GameManager.h"
#include "../../lib/core/WindowManager.h"
#include "../../lib/core/Screen.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/core/ResolutionManager.h"
#include "../../lib/systems/LifeManager.h"
#include "../../lib/systems/EnemySpawner.h"
#include <stdio.h>

#define REF_LARGEUR 1920
#define REF_HAUTEUR 1080

Camera2D camera = { 0 };

// Point d'entrée du jeu
Screen_t Game(Player* player)
{

    /************************
    * INITIALISATION DU JEU
    *************************/
    double timeSpent=0; //temp entre deux tir
    double startReload = -10;
    int monitorHeight = GetMonitorHeight(0);

    /*******************
    * BOUCLE PRINCIPALE
    ********************/
    while (!IsKeyPressed(KEY_ESCAPE) && !endLvl())
    {
        WindowManager_Update(); // Update de l'état de la fenêtre

        camera.target.y = player->position.y + player->size.y - monitorHeight/3;

        // LOGIQUE
        GameUpdate(player, &timeSpent, &startReload);

        // DESSIN
        BeginDrawing();
            ClearBackground(RAYWHITE);   
            BeginMode2D(camera);
                GameDraw(player);
            EndMode2D();

            DrawFPS(10, 10);
            HPDraw(player, 10, 30, (int)(GetScreenWidth() * 0.2f), (int)(GetScreenHeight() * 0.03f));
        EndDrawing();
    }

    if(IsKeyPressed(KEY_ESCAPE))
        return (SCREEN_PAUSE);
    enemySpawner.nbVague = 0;
    currentLevel.enemyCount = -1;
    NextLvlRequest(currentLevel.triggers->action); // Si on met plus de 1 trigger ça va pt
    NewLevel(1);
    return (SCREEN_END_LEVEL);
}


bool endLvl(){
    int i;
    if(enemySpawner.nbVague == currentLevel.enemyCount){
        for(i = 0; enemyPool.tab[i].active == 0 && enemyPool.capacity > i ;i++);
        if(enemyPool.capacity == i) return true;
    }
    return false;
}
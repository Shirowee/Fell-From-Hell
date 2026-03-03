#include <stdlib.h>
#include "../raylib/include/raylib.h"
#include "../lib/core/GameManager.h"
#include "../lib/player/Player.h"
#include "../lib/player/PlayerController.h"
#include "../lib/player/PlayerMovement.h"
#include "../lib/levels/LevelManager.h"

// Declarations
static void TestLevelInit(Platform *platforms[4], int *nbPlatforms);
static void TestLevelFree(Platform **platforms, const int nbPlatforms);
static void TestLevelDraw(Platform **platforms, const int nbPlatforms);

int main(void)
{
    Player player;
    Platform *platforms[6];
    int nbPlatforms = 0;

    InitWindow(800, 450, "Fell From Hell");

    PlayerInit(&player);
    TestLevelInit(platforms, &nbPlatforms);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        PlayerUpdate(&player, platforms, nbPlatforms); // Logique

        BeginDrawing();
        ClearBackground(RAYWHITE);

        TestLevelDraw(platforms, nbPlatforms);   // Dessin des plateformes
        PlayerDraw(&player);                              // Dessin du joueur

        DrawFPS(10, 10);

        EndDrawing();
    }

    TestLevelFree(platforms, nbPlatforms);

    CloseWindow();
    return 0;
}

static
void TestLevelInit (Platform *platforms[4], int *nbPlatforms) {
    Platform *Ground = malloc(sizeof(Platform));
    Platform *Wall1 = malloc(sizeof(Platform));
    Platform *Wall2 = malloc(sizeof(Platform));
    Platform *Roof = malloc(sizeof(Platform));
    Platform *Platform1 = malloc(sizeof(Platform));
    Platform *Platform2 = malloc(sizeof(Platform));

    Ground->rect = (Rectangle){ 0, 400, 800, 50 };
    Wall1->rect = (Rectangle){ 200, 300, 50, 100 };
    Wall2->rect = (Rectangle){ 500, 50, 50, 200 };
    Roof->rect = (Rectangle){ 0, 0, 800, 50 };
    Platform1->rect = (Rectangle){ 10, 250, 200, 10 };
    Platform2->rect = (Rectangle){ 600, 300, 200, 10 };

    Ground->solid = true;
    Wall1->solid = true;
    Wall2->solid = true;
    Roof->solid = true;
    Platform1->solid = false;
    Platform2->solid = false;

    platforms[0] = Ground;
    platforms[1] = Wall1;
    platforms[2] = Wall2;
    platforms[3] = Roof;
    platforms[4] = Platform1;
    platforms[5] = Platform2;

    *nbPlatforms = 6;
}

static
void TestLevelFree(Platform **platforms, const int nbPlatforms) {
    for (int i = 0; i < nbPlatforms; i++) {
        free(platforms[i]);
    }
}

static
void TestLevelDraw(Platform **platforms, const int nbPlatforms) {
    for (int i = 0; i < nbPlatforms; i++) {
        DrawRectangleRec(platforms[i]->rect, DARKGRAY);
    }
}
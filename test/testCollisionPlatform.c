#include <stdlib.h>
#include "../raylib/include/raylib.h"
#include "../lib/core/GameManager.h"
#include "../lib/player/Player.h"
#include "../lib/player/PlayerController.h"
#include "../lib/player/PlayerMovement.h"
#include "../lib/levels/LevelManager.h"
#include "../lib/menu/Screen.h"

Camera2D camera = { 0 };
KeyBindings keys = { KEY_A, KEY_D, KEY_SPACE, KEY_E };

static void TestLevelInit(Platform platforms[8], int *nbPlatforms);
static void TestLevelDraw(Platform platforms[8], const int nbPlatforms);

int main(void)
{
    Player player;
    Platform platforms[8];
    int nbPlatforms = 0;
    double timeSpent = 0;
    double startReload = 0;

    InitWindow(800, 450, "Collision Platform Test");

    PlayerInit(&player);
    TestLevelInit(platforms, &nbPlatforms);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        PlayerUpdate(&player, platforms, nbPlatforms, &timeSpent, &startReload);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        TestLevelDraw(platforms, nbPlatforms);
        PlayerDraw(&player);

        DrawFPS(10, 10);
        DrawText(TextFormat("Movement State: %i", getPlayerMovementState(&player)), 10, 30, 20, GREEN);
        DrawText(TextFormat("Is On Ground: %i", isOnGround(&player, platforms, nbPlatforms)), 10, 50, 20, GREEN);
        DrawText(TextFormat("Is On Ground Config: %i", player.movConfig.isOnGround), 10, 70, 20, ORANGE);
        DrawText(TextFormat("Is On Left Wall Config: %i", player.movConfig.isOnLeftWall), 10, 90, 20, ORANGE);
        DrawText(TextFormat("Is On Right Wall Config: %i", player.movConfig.isOnRightWall), 10, 110, 20, ORANGE);
        DrawText(TextFormat("dashTime: %fs", player.movConfig.dashTime), 500, 70, 20, ORANGE);
        DrawText(TextFormat("dashTimeOut: %fs", player.movConfig.dashTimeOut), 500, 90, 20, ORANGE);
        DrawText(TextFormat("Velocity y: %f", player.velocity.y), 500, 110, 20, ORANGE);
        DrawText(TextFormat("NbJump: %i", player.movConfig.nbJump), 500, 130, 20, ORANGE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

static void TestLevelInit(Platform platforms[8], int *nbPlatforms)
{
    platforms[0].rect = (Rectangle){ 0, 400, 800, 50 };   platforms[0].solid = true;
    platforms[1].rect = (Rectangle){ 0, 0, 50, 450 };     platforms[1].solid = true;
    platforms[2].rect = (Rectangle){ 780, 0, 20, 450 };   platforms[2].solid = true;
    platforms[3].rect = (Rectangle){ 200, 300, 50, 100 }; platforms[3].solid = true;
    platforms[4].rect = (Rectangle){ 500, 50, 50, 200 };  platforms[4].solid = true;
    platforms[5].rect = (Rectangle){ 0, 0, 800, 50 };     platforms[5].solid = true;
    platforms[6].rect = (Rectangle){ 10, 250, 200, 10 };  platforms[6].solid = false;
    platforms[7].rect = (Rectangle){ 600, 300, 200, 10 }; platforms[7].solid = false;
    *nbPlatforms = 8;
}

static void TestLevelDraw(Platform platforms[8], const int nbPlatforms)
{
    for (int i = 0; i < nbPlatforms; i++)
        DrawRectangleRec(platforms[i].rect, DARKGRAY);
}

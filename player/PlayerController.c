#include "PlayerController.h"
#include "PlayerMovement.h"
#include "../raylib/include/raylib.h"

//pos et taille du player
static Vector2 playerPos;
static Vector2 playerSize = { 30, 50 };


//init le joueur
void PlayerInit(void)
{
    playerPos = (Vector2){ 100, 350 };
}

//maj de la logique du player
void PlayerUpdate(void)
{
    PlayerMove(&playerPos);
}

//dessine le joueur
void PlayerDraw(void)
{
    DrawRectangleV(playerPos, playerSize, BLUE);
}

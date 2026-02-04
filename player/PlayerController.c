#include "PlayerController.h"
#include "PlayerMovement.h"
#include "raylib.h"

static Vector2 playerPos;
static Vector2 playerSize = { 30, 50 };

void PlayerInit(void)
{
    playerPos = (Vector2){ 100, 350 };
}

void PlayerUpdate(void)
{
    PlayerMove(&playerPos);
}

void PlayerDraw(void)
{
    DrawRectangleV(playerPos, playerSize, BLUE);
}

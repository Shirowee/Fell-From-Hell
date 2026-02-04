#include "PlayerMovement.h"

#define PLAYER_SPEED 200.0f

void PlayerMove(Vector2* pos)
{
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_RIGHT)) pos->x += PLAYER_SPEED * dt;
    if (IsKeyDown(KEY_LEFT))  pos->x -= PLAYER_SPEED * dt;
}

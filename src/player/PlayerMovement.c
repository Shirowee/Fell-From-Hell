#include "../../lib/player/PlayerMovement.h"

#define PLAYER_SPEED 200.0f //vitesse


//Déplacements latéraux
void PlayerMove(Vector2* pos)
{
    float dt = GetFrameTime(); // Temps entre images

    if (IsKeyDown(KEY_RIGHT)) pos->x += PLAYER_SPEED * dt;
    if (IsKeyDown(KEY_LEFT))  pos->x -= PLAYER_SPEED * dt;
}

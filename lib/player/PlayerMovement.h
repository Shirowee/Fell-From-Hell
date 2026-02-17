#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "../../raylib/include/raylib.h"
#include "../levels/Platform.h"

#define MAX_SPEED 200
#define JUMP_STRENGTH -450
#define GRAVITY 700
typedef struct PlayerMovement {
    Vector2 velocity;
    float maxSpeed;
    float jumpStrength;
    bool isOnGround;
} PlayerMovement;

void PlayerMove(Platform **platform, const int nbPlatforms);
void PlayerJump(void);
void Gravity(void);
void PlayerBodyFix(Platform **platform, const int nbPlatforms);
bool isOnGround(Platform **platform, const int nbPlatforms);

#endif

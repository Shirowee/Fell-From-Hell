#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerMovement.h"
#include "../../raylib/include/raylib.h"

typedef struct PlayerBody {
    Rectangle main;
    Rectangle foot;
} PlayerBody;

typedef struct Player {
    PlayerBody body;
    PlayerMovement movement;
} Player;

extern Player player;

#endif
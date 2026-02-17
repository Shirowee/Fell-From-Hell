#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "../levels/Platform.h"

#define PLAYER_X 100
#define PLAYER_Y 350
#define PLAYER_SIZE_X 30
#define PLAYER_SIZE_Y 50

void PlayerInit(void);
void PlayerUpdate(Platform **platform, const int nbPlatforms);
void PlayerDraw(void);

#endif

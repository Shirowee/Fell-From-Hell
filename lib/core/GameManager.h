#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../player/Player.h"
#include "../systems/BulletPool.h"
#include <stdlib.h>

extern Camera2D camera;

void GameInit(Player *player);
void GameUpdate(Player *player, double* timeSpent, double* startReload);
void GameDraw(Player *player);
void GameUnload(Player player);

#endif

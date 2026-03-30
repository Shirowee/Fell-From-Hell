#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../player/Player.h"
#include "../systems/BulletPool.h"
#include <stdlib.h>
#include <time.h>

void GameInit(Player *player, float dynamicTileSize);
void GameUpdate(Player *player, double* timeSpent, double* startReload);
void GameDraw(Player *player);
void GameUnload(void);

#endif

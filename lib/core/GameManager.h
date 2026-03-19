#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../player/Player.h"

void GameInit(Player *player, float dynamicTileSize);
void GameUpdate(Player *player);
void GameDraw(Player *player);
void GameUnload(void);

#endif

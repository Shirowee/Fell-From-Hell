/**
 * \file PlayerController.h
 * \brief Gère l'initialisation, la mise à jour et le dessin du joueur.
 * \author Caius
 * \version 0.1
 * \date 21-02-2026
 */

#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "../levels/Platform.h"
#include "Player.h"

#define PLAYER_X 100
#define PLAYER_Y 350
#define PLAYER_SIZE_X 30
#define PLAYER_SIZE_Y 50

void PlayerInit(Player *player);
void PlayerUpdate(Player *player, Platform platform[], const int nbPlatforms, double* timeSpent, double* startReload);
void PlayerDraw(Player *player);

#endif

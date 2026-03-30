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

/**
 * \def PLAYER_X
 * \brief Position par défaut du joueur sur l'axe x en pixels.
 */
#define PLAYER_X 100
/**
 * \def PLAYER_Y
 * \brief Position par défaut du joueur sur l'axe y en pixels.
 */
#define PLAYER_Y 350
/**
 * \def PLAYER_SIZE_X
 * \brief Taille par défaut du joueur sur l'axe x en pixels.
 */
#define PLAYER_SIZE_X 30
/**
 * \def PLAYER_SIZE_Y
 * \brief Taille par défaut du joueur sur l'axe y en pixels.
 */
#define PLAYER_SIZE_Y 50

 /**
 * \fn void PlayerInit(Player *player);
 * \brief Initialise la structure joueur
 * \param player Pointeur sur Player
 */
void PlayerInit(Player *player);

 /**
 * \fn void PlayerUpdate(Player *player, Platform platform[], const int nbPlatforms, double* timeSpent, double* startReload);
 * \brief Met à jour le joueur,
 * c-à-d mettre à jour les inputs du joueur, 
 * les mouvements du joueur, 
 * les armes du joueur et les configurations liés au joueur.
 * \param player Pointeur sur Player
 * \param platform Tableau de platform
 * \param nbPlatforms Taille de platform
 * \param timeSpent Temps écoulé depuis le tir de la dernière balle
 * \param startReload Temps écoulé depuis le dernier rechargement de l'arme
 */
void PlayerUpdate(Player *player, Platform platform[], const int nbPlatforms, double* timeSpent, double* startReload);

 /**
 * \fn void PlayerDraw(Player *player);
 * \brief Dessine le joueur sur l'écran du jeu
 * \param player Pointeur sur Player
 */
void PlayerDraw(Player *player);

#endif

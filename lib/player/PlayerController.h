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
#define PLAYER_SIZE_X 64
/**
 * \def PLAYER_SIZE_Y
 * \brief Taille par défaut du joueur sur l'axe y en pixels.
 */
#define PLAYER_SIZE_Y 128
/**
 * \def DEFAULT_PLAYER_HP
 * \brief Nombre de points de vie par défaut du joueur
 */
#define DEFAULT_PLAYER_HP 200
/**
 * \def DEFAULT_PLAYER_REGEN
 * \brief Nombre de points de vie régénéré par défaut au joueur
 */
#define DEFAULT_PLAYER_REGEN 5
/**
 * \def PLAYER_INVICIBILITY_TIME
 * \brief Temps d'invincibilité du joueur
 */
#define PLAYER_INVICIBILITY_TIME 1


/*
 *Structures
 */

 /**
 * \struct PlayerStats_s
 * \brief Structure pour les statistiques du joueur.
 * \typedef PlayerStats
 * \brief Type de données pour les statistiques du joueur.
 */
typedef struct PlayerStats_s{
    int hp; /**< Points de vie courant */
    int hpMax;  /**< Points de vie maximale */
    int regen;  /**< Nombre de points de vie régénéré par seconde */
    float regenTimeOut;   /**< Temps avant que la vie du joueur se régénère */
    float invTime; /**< Temps pendant lequel le joueur est invincible */
}PlayerStats;

#include "Player.h"

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
Vector2 getPlayerCenter(Player *player);

#endif

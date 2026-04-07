/**
 * \file Player.h
 * \brief Définit la structure du joueur et son corps, ainsi que les fonctions associées
 * \author Caius
 * \version 0.1
 * \date 21-02-2026
 */

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player_s Player;

#include "PlayerController.h"
#include "PlayerMovement.h"
#include "PlayerWeapon.h"
#include "../../raylib/include/raylib.h"

/*
 *Structures
 */

/**
 * \struct Player_s
 * \brief Structure pour gérer le joueur.
 * \typedef Player
 * \brief Type de données pour le joueur.
 */
struct Player_s {
    Vector2 position;           /**< Position du joueur */
    Vector2 size;               /**< Taille du joueur */
    Vector2 velocity;           /**< Vecteur de vitesse du joueur */
    PlayerStats stats;          /**< Statistiques du joueur */
    MovementConfig movConfig;  /**< Configuration de mouvement du joueur */
    weapon_t weapon;            /**< Arme du joueur */
};

#endif
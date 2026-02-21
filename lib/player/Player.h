/**
 * \file Player.h
 * \brief Définit la structure du joueur et son corps, ainsi que les fonctions associées
 * \author Caius
 * \version 0.1
 * \date 21-02-2026
 */

#ifndef PLAYER_H
#define PLAYER_H

typedef struct PlayerBody_s PlayerBody;
typedef struct Player_s Player;

#include "PlayerMovement.h"
#include "../../raylib/include/raylib.h"

/*
 *Structures
 */

/**
 * \struct PlayerBody_s
 * \brief Structure pour gérer le corps du joueur.
 * \typedef PlayerBody
 * \brief Type de données pour le corps du joueur.
 * \details Cette structure sépare le corps du joueur en deux parties : la partie principale et la partie inférieure du corps. Cette séparation permet une meilleure gestion des collisions avec les plateformes.
 */
struct PlayerBody_s {
    Rectangle main; /**< Rectangle représentant la partie principale du corps du joueur. Servant pour les collisions avec les plateformes. */
    Rectangle foot; /**< Rectangle représentant la partie inférieure du corps du joueur. Servant pour vérifier si le joueur est au sol. */
};

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
    PlayerBody body;            /**< Corps du joueur, servant principalement pour les collisions */
    MovementConfig movConfig;  /**< Configuration de mouvement du joueur */
};

#endif
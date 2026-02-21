/**
 * \file PlayerMovement.h
 * \brief Gère les mouvements du joueur, y compris les déplacements latéraux, les sauts, la gravité et les collisions avec les plateformes.
 * \author Caius
 * \version 0.1
 * \date 21-02-2026
 */

#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "../../raylib/include/raylib.h"
#include "../levels/Platform.h"

/*
 *Constantes
 */

 /**
 * \def GROUND_ACC
 * \brief accélération du joueur sur le sol en pixels par seconde.
 */
#define GROUND_ACC 100
/**
 * \def MAX_SPEED
 * \brief Vitesse maximale du joueur en pixels par seconde.
 */
#define MAX_SPEED 400
/**
 * \def JUMP_STRENGTH
 * \brief Force de saut du joueur en pixels par seconde.
 */
#define JUMP_STRENGTH -600
/**
 * \def DEFAULT_GRAVITY
 * \brief Gravité par défaut en pixels par seconde carrée.
 */
#define DEFAULT_GRAVITY 980

/*
 *Structures
 */

/**
 * \enum PlayerState_s
 * \brief Enumeration des états de mouvement possibles du joueur.
 * \typedef PlayerState
 * \brief Type de données pour les états de mouvement possibles du joueur.
 */
typedef enum MovementState_s {
    IDLE,
    RUNNING,
    JUMPING,
    FALLING,
    WALL_SLIDING
} MovementState;

/**
 * \struct MovementConfig_s
 * \brief Structure pour gérer les mouvements du joueur.
 * \typedef MovementConfig
 * \brief Type de données pour les mouvements du joueur.
 */
typedef struct MovementConfig_s {
    float maxSpeed;     /**< Vitesse maximale du joueur */
    float groundAcc;     /**< Accélération du joueur au sol */
    float jumpStrength; /**< Force de saut du joueur */
    float gravity;      /**< Gravité appliquée au joueur */

    bool isOnGround;    /**< Indique si le joueur est au sol */
    bool isOnLeftWall;   /**< Indique si le joueur est en train de glisser sur un mur à gauche */
    bool isOnRightWall;  /**< Indique si le joueur est en train de glisser sur un mur à droite */
} MovementConfig;

#include "Player.h"

/*
 *Fonctions
 */

void PlayerMove(Player *player, Platform **platform, const int nbPlatforms);
void PlayerJump(Player *player);
void Gravity(Player *player, const float GravityStrength);
void PlayerPositionFix(Player *player, Platform **platform, const int nbPlatforms);
bool isOnGround(Player *player, Platform **platform, const int nbPlatforms);
MovementState getPlayerMovementState(Player *player);

#endif

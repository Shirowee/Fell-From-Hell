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
#define GROUND_ACC 1600
 /**
 * \def AIR_ACC
 * \brief accélération du joueur dans les airs en pixels par seconde.
 */
#define AIR_ACC 1000
/**
 * \def MAX_SPEED
 * \brief Vitesse maximale du joueur en pixels par seconde.
 */
#define MAX_SPEED 400
/**
 * \def MAX_WALL_SPEED
 * \brief Vitesse maximale du joueur sur mur en pixels par seconde.
 */
#define MAX_WALL_SPEED 200
/**
 * \def JUMP_STRENGTH
 * \brief Force de saut du joueur en pixels par seconde.
 */
#define JUMP_STRENGTH -800
/**
 * \def DASH_SPEED
 * \brief Vitesse du dash du joueur en pixels par seconde.
 */
#define DASH_SPEED 800
/**
 * \def DEFAULT_GRAVITY
 * \brief Gravité par défaut en pixels par seconde carrée.
 */
#define DEFAULT_GRAVITY 980
/**
 * \def FALLING_GRAVITY
 * \brief Gravité lors d'une chute en pixels par seconde carrée.
 */
#define FALLING_GRAVITY 1225
/**
 * \def WALL_SLIDE_GRAVITY
 * \brief Gravité sur mur en pixels par seconde carrée.
 */
#define WALL_SLIDE_GRAVITY 300
/**
 * \def GROUND_FRICTION
 * \brief Ralentissement par friction sur le sol
 */
#define GROUND_FRICTION 0.0001
/**
 * \def AIR_FRICTION
 * \brief Ralentissement par friction dans les airs
 */
#define AIR_FRICTION 0.1
/**
 * \def DEFAULT_JUMPS_MAX
 * \brief Nombre de saut d'affilé maximum par défaut
 */
#define DEFAULT_JUMPS_MAX 3

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
    WALL_SLIDING,
    DASHING
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
    float airAcc;     /**< Accélération du joueur dans les airs */
    float jumpStrength; /**< Force de saut du joueur */
    float gravity;      /**< Gravité appliquée au joueur */
    float fallingGravity;      /**< Gravité appliquée au joueur lorsqu'il tombe */

    int nbJumpMax;  /**< Nombre de saut d'affilé maximum */
    int nbJump;     /**< Nombre de saut d'affilé restant */

    bool isOnGround;    /**< Indique si le joueur est au sol */
    bool isOnLeftWall;   /**< Indique si le joueur est entrain de glisser sur un mur à gauche */
    bool isOnRightWall;  /**< Indique si le joueur est entrain de glisser sur un mur à droite */
    bool isDashing;     /**< Indique si le joueur est entrain de glisser */
} MovementConfig;
/**
 * \struct MovFlags_s
 * \brief Structure pour gérer les flags de mouvements du joueur.
 * \typedef MovFlags
 * \brief Type de données pour les flags de mouvements du joueur.
 */
typedef struct MovFlags_s {
    bool jumpMovePressed;
} MovFlags;

/**
 * \struct MovTimer_s
 * \brief Structure pour gérer les chronomètres de mouvements du joueur.
 * \typedef MovTimer
 * \brief Type de données pour les chronomètres de mouvements du joueur.
 */
typedef struct MovTimer_s {
    float jumpTime;
    float jumpTimeOut;
    float dashTime;
    float dashTimeOut;
} MovTimer;

/**
 * \enum Direction
 * \brief Enumeration des directions.
 */
typedef enum{Left, Right, Up, Down} Direction;

#include "Player.h"

/*
 *Fonctions
 */

 /**
 * \fn void PlayerMove(Player *player, Platform **platform, const int nbPlatforms);
 * \brief Execute les mouvements du joueur dans un niveau et met à jour les configurations de ses mouvements
 * \param player Pointeur sur Player
 * \param platform Tableau de pointeurs sur Platform
 * \param nbPlatform Nombre de Platform dans le tableau platform
 */
void PlayerMove(Player *player, Platform platform[], const int nbPlatforms);

 /**
 * \fn void PlayerMoveFlagsInit();
 * \brief Initialise les flags de mouvements du joueur
 */
void PlayerMoveFlagsInit();

 /**
 * \fn void PlayerMoveTimerInit();
 * \brief Initialise les chronomètres de mouvements du joueur
 */
void PlayerMoveTimerInit();

 /**
 * \fn void PlayerMoveFlagsUpdate();
 * \brief Met à jour les flags de mouvements du joueur
 */
void PlayerMoveFlagsUpdate();

 /**
 * \fn void PlayerMoveTimerUpdate(Player *player);
 * \brief Met à jour les chronomètres de mouvements du joueur
 */
void PlayerMoveTimerUpdate(Player *player);

 /**
 * \fn void PlayerMoveConfigUpdate(Player *player, Platform **platform, const int nbPlatforms);
 * \brief Met à jour les configs des mouvements
 * \param player Pointeur sur Player
 * \param platform Tableau de pointeurs sur Platform
 * \param nbPlatform Nombre de Platform dans le tableau platform
 */
void PlayerMoveConfigUpdate(Player *player, Platform platform[], const int nbPlatforms);

/**
 * \fn void PlayerJump(Player *player);
 * \brief Fait sauter le joueur
 * \param player Pointeur sur Player
 */
void PlayerJump(Player *player);

void PlayerDash(Player *player);

/**
 * \fn void Gravity(Player *player, const float GravityStrength);
 * \brief Applique force de gravité sur le joueur
 * \param player Pointeur sur Player
 * \param GravityStrength Force de gravité
 */
void Gravity(Player *player, const float GravityStrength);
/**
 * \fn void PlayerPositionFix(Player *player, Platform **platform, const int nbPlatforms);
 * \brief Corrige la position du joueur en cas de collision avec un ou des Platform
 * \param player Pointeur sur Player
 * \param platform Tableau de pointeurs sur Platform
 * \param nbPlatform Nombre de Platform dans le tableau platform
 */
void PlayerPositionFix(Player *player, Platform platform[], const int nbPlatforms);
/**
 * \fn bool isOnGround(Player *player, Platform **platform, const int nbPlatforms);
 * \brief Verifie si le joueur est sur une Platform
 * \param player Pointeur sur Player
 * \param platform Tableau de pointeurs sur Platform
 * \param nbPlatform Nombre de Platform dans le tableau platform
 * \return true si le joueur est bien sur une Platform, sinon false
 */
bool isOnGround(Player *player, Platform platform[], const int nbPlatforms);
/**
 * \fn bool isOnWall(Player *player, Platform **platform, const int nbPlatforms, Direction dir);
 * \brief Verifie si le joueur est sur un mur
 * \param player Pointeur sur Player
 * \param platform Tableau de pointeurs sur Platform
 * \param nbPlatform Nombre de Platform dans le tableau platform
 * \param dir Direction vers laquelle il faut vérifier
 * \return true si le joueur est bien sur un mur, sinon false
 */
bool isOnWall(Player *player, Platform platform[], const int nbPlatforms, Direction dir);

/**
 * \fn MovementState getPlayerMovementState(Player *player);
 * \brief Verifie l'etat de mouvement du joueur
 * \param player Pointeur sur Player
 * \return MovementState correspondant a l'etat de mouvement du joueur
 */
MovementState getPlayerMovementState(Player *player);

extern MovTimer timer;

#endif

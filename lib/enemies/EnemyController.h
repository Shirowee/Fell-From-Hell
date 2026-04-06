/**
 * @file EnemyController.h
 * @brief Gestion des ennemis et de leur comportement (state machine)
 * 
 * Définit l’interface de contrôle des ennemis du jeu.
 * Implémente une machine à états permettant de gérer différents
 * comportements tels que :
 * - déplacement aléatoire
 * - poursuite du joueur
 * - attaque
 * - états passifs ou inactifs
 *
 * Chaque ennemi est représenté par une structure 'enemy_t' et peut
 * évoluer dynamiquement selon son état interne.
 *
 * Fournit également des fonctions de :
 * - initialisation des ennemis
 * - mise à jour des comportements
 * - gestion des transitions d’états
 * - rendu graphique
 *
 *
 * @author A. Pocholle
 */

#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include "../../raylib/include/raylib.h"
#include "../../lib/systems/BulletPool.h"

/**
 * @brief Types d'ennemis disponibles
 */
typedef enum {
    ENEMY_CHASER,
    ENEMY_SHOOTER,
} EnemyType;

/**
 * @brief Structure représentant un ennemi
 */
typedef struct enemy_s {
    
    /* ==================== Informations générales ==================== */
    float speed; /**< Vitesse de déplacement */
    Vector2 size;  /**< Taille de l'ennemi */
    int dmg; /**< Dégâts infligés */
    Vector2 pos; /**< Position actuelle */
    int dir; /**< Direction */
    int bulletSpeed; /**< Vitesse des projectiles */
    int bulletSize; /**< Taille des projectiles */

    /* ==================== State machine ==================== */
    EnemyType type; /**< Type d'ennemi */

    /**
     * @brief Fonction représentant l'état courant
     * 
     * Pointeur de fonction vers un état (Idle, Move, Attack...)
     */
    void (*state)(struct enemy_s*, bulletPool_t*, Vector2);

    float stateTimer;/**< Timer pour gérer les transitions d'état */

    /* ==================== Logique ==================== */

    int isShooting; /**< Indique si l'ennemi doit tirer au prochain update */
    int active; /**< Indique si l'ennemi est actif (présent à l'écran) */
} enemy_t;

/**
 * @brief Initialise un ennemi
 * 
 * @param enemy pointeur vers l'ennemi
 * @param speed vitesse de déplacement
 * @param size taille de l'ennemi
 * @param dmg dégâts infligés
 * @param pos position initiale
 * @param bulletSpeed vitesse des projectiles
 * @param bulletSize taille des projectiles
 */
void EnemyInit(enemy_t * enemy, float speed, Vector2 size, int dmg, Vector2 pos, int bulletSpeed, int bulletSize);

/**
 * @brief Met à jour la logique de l'ennemi
 * 
 * @param enemy pointeur vers l'ennemi
 * @param playerPos position du joueur
 */
void EnemyUpdate(enemy_t * enemy, Vector2 playerPos);

/**
 * @brief Dessine l'ennemi à l'écran
 * 
 * @param enemy pointeur vers l'ennemi
 */
void EnemyDraw(enemy_t * enemy);

/**
 * @brief Active le tir de l'ennemi
 * 
 * @param enemy pointeur vers l'ennemi
 */
void EnemyShoots(enemy_t * enemy);

/* ==================== États ==================== */

/**
 * @brief Etat idle de l'ennemi
 * @param enemy pointeur vers l'ennemi
 * @param pool pool de bullets
 * @param playerPos position du joueur
 */
void EnemyState_Idle(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);

/**
 * @brief Etat de déplacement
 * @param enemy pointeur vers l'ennemi
 * @param pool pool de bullets
 * @param playerPos position du joueur
 */
void EnemyState_Move(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);

/**
 * @brief Etat d'attaque
 * @param enemy pointeur vers l'ennemi
 * @param pool pool de bullets
 * @param playerPos position du joueur
 */
 */
void EnemyState_Attack(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);

#endif

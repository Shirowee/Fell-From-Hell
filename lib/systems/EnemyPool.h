/**
 * @file EnemyPool.c
 * @brief Gestion du pool d'ennemis (object pooling)
 * @author A. Pocholle
 * 
 * Implémente un système de pool d'ennemis basé sur
 * l’object pooling.
 * 
 * Les ennemis sont pré-alloués dans un tableau et réutilisés
 * via un flag "active", évitant les allocations dynamiques
 * répétées en jeu.
 * 
 * Fonctionnalités :
 * - Initialisation du pool
 * - Spawn d’ennemis
 * - Mise à jour des ennemis
 * - Affichage des ennemis
 * - Libération mémoire
 */

#ifndef ENEMYPOOL_H
#define ENEMYPOOL_H

#include "../../raylib/include/raylib.h"
#include "../enemies/EnemyController.h"




typedef struct enemyPool_s {
    enemy_t* tab; //liste contenant les enemy
    int active; //booléen pour l'activité de la pool
    int nbEnemiesActive; //nombre d'ennemis actifs
    int capacity; //nombre d'elements
} enemyPool_t;

/**
 * @brief Initialise un pool d’ennemis
 * 
 * Alloue dynamiquement un tableau d’ennemis et initialise
 * chaque entrée comme inactive.
 * 
 * @param pool pointeur vers le pool à initialiser
 * @param capacity nombre maximum d’ennemis
 */
void InitEnemyPool(enemyPool_t* pool, int capacity);

/**
 * @brief Fait apparaître un ennemi dans le pool
 * 
 * Recherche la première entrée inactive pour la réutiliser.
 * Si aucun slot n’est disponible, aucun ennemi n’est créé.
 * 
 * @param pool pointeur vers le pool
 * @param pos position de spawn
 * @param speed vitesse de déplacement
 * @param size taille de l’ennemi
 * @param dmg dégâts infligés
 * @param bulletSpeed vitesse des projectiles
 * @param bulletSize taille des projectiles
 */
void SpawnEnemyPool(enemyPool_t* pool, 
    Vector2 pos, 
    int hp,
    float speed, 
    Vector2 size, 
    int dmg, 
    float bulletSpeed, 
    int bulletSize, 
    EnemyType_t type);

/**
 * @brief Met à jour tous les ennemis du pool
 * 
 * @param pool pointeur vers le pool
 * @param playerPos position du joueur
 */
void UpdateEnemyPool(enemyPool_t* pool, Vector2 playerPos);

/**
 * @brief Dessine tous les ennemis actifs
 * 
 * @param pool pointeur vers le pool
 * @param playerPos position du joueur
 */
void DrawEnemyPool(enemyPool_t* pool, Vector2 playerPos);

/**
 * @brief Libère la mémoire du pool d’ennemis
 * 
 * @param pool pointeur vers le pool
 */
void FreeEnemyPool(enemyPool_t* pool);

/** @brief Pool global d’ennemis */
extern enemyPool_t enemyPool;
#endif
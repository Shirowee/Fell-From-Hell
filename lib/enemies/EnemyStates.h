/**
 * @file EnemyStates.h
 * @brief Machine à états des ennemis
 *
 * Définit la machine à états utilisée pour contrôler
 * le comportement des ennemis dans le jeu.
 *
 * Chaque ennemi possède un état courant qui détermine son comportement,
 * par exemple :
 * - état de base (idle)
 * - déplacement (move)
 * - poursuite du joueur (chase)
 * - attaque (attack)
 *
 * Les transitions entre états sont gérées en fonction de conditions
 * internes (distance au joueur, timer, dégâts, etc.).
 *
 *
 * @author A. Pocholle
 */
 
#ifndef ENEMY_STATES_H
#define ENEMY_STATES_H

#include "../../lib/enemies/EnemyController.h"
#include "../systems/BulletPool.h"

/**
 * @brief Etat idle de l'ennemi
 * 
 * Choisit le prochain état en fonction du type d'ennemi :
 * - CHASER : poursuite du joueur
 * - SHOOTER : attaque ou déplacement aléatoire
 */
void EnemyState_Idle(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);

/**
 * @brief Etat de poursuite du joueur
 */
void EnemyState_MoveTowardsPlayer(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);

/**
 * @brief Etat de déplacement aléatoire
 * 
 * - Change de direction toutes les secondes
 * - Se déplace continuellement
 * - Retourne en idle après 3 secondes
 */
void EnemyState_MoveRandom(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos);

/**
 * @brief Etat d'attaque circulaire
 * 
 * Tire des projectiles en cercle autour de l'ennemi
 */
void EnemyState_EnemyShootCircle(enemy_t* enemy, bulletPool_t* pool, Vector2 playerPos);

/**
 * @brief Etat d'attaque simple
 * 
 * Tire un projectile en ligne droite vers le joueur
 */
void EnemyState_EnemyShoot(enemy_t* enemy, bulletPool_t* pool, Vector2 playerPos);

/**
 * @brief Etat d'attaque en spirale
 * 
 * Tire un projectile en spirale autour de l'ennemi
 */
void EnemyState_EnemyShootSpiral(enemy_t* enemy, bulletPool_t* pool, Vector2 playerPos);

/**
 * @brief Etat d'attaque en arc
 * 
 * Tire des projectiles en arc de cercle vers le joueur
 */
void EnemyState_EnemyShootArc(enemy_t* enemy, bulletPool_t* pool, Vector2 playerPos);

#endif
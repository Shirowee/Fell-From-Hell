/**
 * @file CollisionSystem.c
 * @brief Gestion des collisions entre ennemis et projectiles
 * @author A. Pocholle
 *
 * Ce fichier implémente la détection de collision entre les ennemis
 * et les bullets à l’aide d’une méthode simple basée sur la distance
 * entre deux points (collision circulaire).
 * 
 * Lorsqu'une collision est détectée :
 * - l'ennemi est désactivé
 * - la bullet est désactivée
 */


#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "EnemyPool.h"
#include "BulletPool.h"
#include "../player/Player.h"

/**
 * @brief Détecte les collisions entre ennemis et projectiles
 * 
 * Parcourt tous les ennemis actifs et toutes les bullets actives,
 * puis vérifie si la distance entre eux est inférieure à la somme
 * de leurs rayons.
 * 
 * @param enemies pool d’ennemis
 * @param bullets pool de projectiles
 */
void CheckEnemyBulletCollision(enemyPool_t* enemies, bulletPool_t* bullets);

/**
 * @brief Détecte collisions entre joueur et ennemies et calcule le nombre de dégâts total à infliger
 * 
 * @param player Pointeur vers le joueur
 * @param enemies Pool d'ennemis
 * @param[out] dmg Dégâts à infliger
 */
void CheckPlayerEnemyCollision(Player* player, enemyPool_t* enemies, int* total_dmg);

/**
 * @brief Détecte collisions entre joueur et projectiles et calcule le nombre de dégâts total à infliger
 * 
 * @param player Pointeur vers le joueur
 * @param bullets Pool de projectiles
 * @param[out] dmg Dégâts à infliger
 */
void CheckPlayerBulletCollision(Player* player, bulletPool_t* bullets, int* total_dmg);

/**
 * @brief Détecte collisions entre les projectiles et les platformes
 * 
 * @param bullets Pool de projectiles
 * @param platforms Tableau de platformes
 * @param nbPlatforms Nombre de platformes
 */
void CheckBulletsPlatformsCollision(bulletPool_t *bullets, Platform platforms[], const int nbPlatforms);

/**
 * @brief Corrige la position du joueur en cas de collision avec les platformes
 * 
 * Utilise l'algorithme AABB Collision Resolution
 * 
 * @param player Pointeur vers le joueur
 * @param oldPosition Ancienne coordonnées du joueur
 * @param platform Tableau de platformes
 * @param nbPlatform Nombre de platformes
 */
void PlayerPositionFix(Player *player, const Vector2 oldPosition, Platform platform[], const int nbPlatforms);

/**
 * @brief Corrige la position des ennemis en cas de collision avec les platformes
 * 
 * Utilise l'algorithme AABB Collision Resolution
 * 
 * @param enemies Pool d'ennemis
 * @param platform Tableau de plateformes
 * @param nbPlatform Nombre de platformes
 */
void EnemiesPositionFix(enemyPool_t *enemies, Platform platform[], const int nbPlatforms);

#endif
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

#endif
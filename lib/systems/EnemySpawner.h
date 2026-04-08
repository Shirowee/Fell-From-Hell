/**
 * @file EnemySpawner.c
 * @brief Gestion de l'apparition dynamique des ennemis
 * @author A. Pocholle
 *
 * Responsable du spawn automatique des ennemis
 * à intervalles réguliers.
 * 
 * Le système fonctionne avec :
 * - un timer interne
 * - un cooldown variable
 * - un spawn aléatoire sur l'écran
 */

#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "../../lib/systems/EnemyPool.h"

/**
 * @struct EnemySpawner
 * @brief Gère le système de spawn des ennemis
 *
 * Permet de contrôler l’apparition des ennemis
 * dans le jeu via un système de timer et de cooldown.
 *
 * Le timer accumule le temps écoulé,
 * et le cooldown définit le temps minimum entre deux spawns.
 */
typedef struct {
    float timer;
    float cooldown;
} EnemySpawner;

/**
 * @brief Initialise le spawner d'ennemis
 * 
 * @param spawner pointeur vers le spawner
 */
void EnemySpawnerInit(EnemySpawner* spawner);

/**
 * @brief Spawn un ennemi à une position aléatoire
 * 
 * Génère un ennemi avec des statistiques aléatoires :
 * - position sur l'écran
 * - vitesse
 * - taille
 * - dégâts
 * - caractéristiques des projectiles
 * 
 * @param pool pool d’ennemis
 */
void SpawnRandomEnemy(enemyPool_t* pool);

/**
 * @brief Met à jour le spawner d'ennemis
 * 
 * Incrémente un timer et déclenche un spawn lorsque
 * le cooldown est atteint.
 * Le cooldown est ensuite réinitialisé aléatoirement.
 * 
 * @param spawner pointeur vers le spawner
 * @param pool pool d’ennemis
 */
void UpdateEnemySpawner(EnemySpawner* spawner, enemyPool_t* pool);

/**
 * @brief Spawn un pattern d'enemis
 * 
 * 5 chasers
 * 
 * @param spawner pointeur vers le spawner
 * @param pool pool d’ennemis
 * @param pos position de spawn
 */
void SpawnEnemyPattern1(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos);
extern EnemySpawner enemySpawner;
#endif
#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "EnemyPool.h"
#include "BulletPool.h"
#include "../player/Player.h"

void CheckEnemyBulletCollision(enemyPool_t* enemies, bulletPool_t* bullets);

/**
 * \fn void CheckPlayerEnemyCollision(Player* player, enemyPool_t* enemies, int* total_dmg);
 * \brief Détecte collisions entre joueur et ennemies et calcule le nombre de dégâts total à infliger
 * \param player Pointeur sur Player
 * \param enemies Tableau contenant les ennemies
 * \param[out] dmg Dégâts à infliger
 */
void CheckPlayerEnemyCollision(Player* player, enemyPool_t* enemies, int* total_dmg);

/**
 * \fn void CheckPlayerEnemyCollision(Player* player, enemyPool_t* enemies, int* total_dmg);
 * \brief Détecte collisions entre joueur et bullets et calcule le nombre de dégâts total à infliger
 * \param player Pointeur sur Player
 * \param bullets Tableau contenant les bullets
 * \param[out] dmg Dégâts à infliger
 */
void CheckPlayerBulletCollision(Player* player, bulletPool_t* bullets, int* total_dmg);

#endif
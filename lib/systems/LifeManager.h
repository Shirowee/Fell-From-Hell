/**
 * \file LifeManager.h
 * \brief Gère la vie du joueur, des balles et des ennemies.
 * \author Caius
 * \version 0.1
 * \date 07-04-2026
 */

#ifndef LIFE_MANAGER_H
#define LIFE_MANAGER_H

#include "../../lib/player/Player.h"
#include "../../lib/systems/EnemyPool.h"


/**
 * \fn void PlayerLifeAlteration(Player *player, enemyPool_t *ennemies, bulletPool_t *bullets);
 * \brief Fait subir des dêgats au joueur en fonction des ennemies et des bullets ou régénère la vie du joueur
 * \param player Pointeur sur Player
 * \param enemies Tableau contenant les ennemies
 * \param bullets Tableau contenant les bullets
 */
void PlayerLifeAlteration(Player *player, enemyPool_t *enemies, bulletPool_t *bullets);

/**
 * \fn void HPDraw(Player *player, int x, int y, int width, int height);
 * \brief Dessine la barre de vie du joueur
 * \param player Pointeur sur Player
 * \param x position sur l'axe x
 * \param y position sur l'axe y
 * \param width longueur de la barre
 * \param height largeur de la barre
 */
void HPDraw(Player *player, int x, int y, int width, int height);

/**
 * \fn ApplyDamageToPlayer(Player *player, int dmg);
 * \brief Applique des dégâts au joueur, c-à-d lui retirer des points de vie
 * \param player Pointeur sur Player
 * \param dmg Nombre de points de vie à retirer
 */
void ApplyDamageToPlayer(Player *player, int dmg);

/**
 * \fn ApplyDamageToPlayer(Player *player, int dmg);
 * \brief Applique des dégâts à l'ennemie, c-à-d lui retirer des points de vie
 * \param enemy Pointeur sur Enemy
 * \param dmg Nombre de points de vie à retirer
 */
void ApplyDamageToEnemy(enemy_t *enemy, int dmg);

/**
 * \fn bool isInvicible(Player *player);
 * \brief Détermine si le joueur est invincible
 * \param player Pointeur sur Player
 * \return Renvoie vrai si il est invincible, sinon faux
 */
bool isInvicible(Player *player);

/**
 * \fn bool isAlive(Player *player);
 * \brief Détermine si le joueur est encore en vie
 * \param player Pointeur sur Player
 * \return Renvoie vrai si il a encore des points de vie, sinon faux
 */
bool isAlive(Player *player);

/**
 * \fn canRegen(Player *player);
 * \brief Détermine si le joueur peut régénérer ses points de vie
 * \param player Pointeur sur Player
 * \return Renvoie vrai si c'est le cas, sinon faux
 */
bool canRegen(Player *player);

#endif
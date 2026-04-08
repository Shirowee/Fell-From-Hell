/**
 * @file EnemyMovement.h
 * @brief Gestion du mouvement des ennemis
 *
 * Contient les fonctions responsables du déplacement
 * des ennemis dans le jeu.
 *
 * Implémente différentes logiques de mouvement selon le type
 * ou l’état de l’ennemi, par exemple :
 * - déplacement aléatoire
 * - poursuite du joueur
 * - déplacement directionnel simple
 * - comportement basé sur une machine à états
 *
 *
 * @author A. Pocholle
 */

#include "../../lib/enemies/EnemyController.h"

#ifndef ENEMY_MOVEMENT_H
#define ENEMY_MOVEMENT_H

/**
 * @brief Déplace l'ennemi selon sa direction actuelle
 * 
 * Utilise la direction (en degrés) et la vitesse pour calculer
 * un déplacement basé sur le temps de frame.
 * 
 * @param enemy pointeur vers l'ennemi
 */
void EnemyMove(enemy_t * enemy);

/**
 * @brief Déplace l'ennemi vers la position du joueur
 * 
 * Calcule la direction vers le joueur, normalise ce vecteur,
 * puis déplace l'ennemi dans cette direction en fonction de sa vitesse
 * et du temps de frame.
 * 
 * @param enemy pointeur vers l'ennemi
 * @param player position du joueur
 */
void EnemyMoveTowardsPlayer(enemy_t * enemy, Vector2 player);

/**
 * @brief Change la direction de l'ennemi pour qu'il regarde vers le joueur
 * 
 * Calcule la direction vers le joueur, normalise ce vecteur,
 * puis change la direction de l'ennemi pour qu'il regarde vers le joueur.
 * 
 * @param enemy pointeur vers l'ennemi
 * @param player position du joueur
 */
void EnemySetDirTowardsPlayer(enemy_t * enemy, Vector2 player);

#endif

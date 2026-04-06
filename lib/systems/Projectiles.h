/**
 * @file Projectiles.c
 * @brief Gestion des projectiles du jeu
 * @authors A. Pocholle, Kilian
 *
 * Ce module gère la création, la mise à jour et l'affichage
 * des projectiles.
 *
 * Plusieurs types de projectiles sont supportés :
 * - BASIC : projectile classique
 * - EXPLOSIF : projectile avec explosion
 * - RAYON : tir instantané type laser
 * - MELEE : (non implémenté)
 */


#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "../../raylib/include/raylib.h"

//differents type de bullet
#define BASIC 0
#define EXPLOSIF 1
#define RAYON 2
#define MELEE 3

/**
 * @struct bullet_s
 * @brief Représente un projectile dans le jeu
 *
 * Contient toutes les informations nécessaires
 * pour gérer un projectile : mouvement, dégâts, durée de vie
 * et type de comportement.
 *
 * Le comportement du projectile dépend du champ `indice`
 * (BASIC, EXPLOSIF, RAYON, MELEE).
 */
typedef struct bullet_s {
    float bulletSpeed; // vitesse
    float bulletSize; // taille
    int bulletDmg; // dégats
    Vector2 bulletPos; // position
    int bulletDir; // direction en deg
    double createTime; //heure de creation
    float lifeTime; //durer de vie (pour bullet explosif et rayon)
    int indice; // indice (BASIC EXPLOSIF RAYON MELEE)
    int active; //si elle doit être dessinée
} bullet_t;

/**
 * @brief Initialise un projectile
 *
 * @param bullet pointeur vers le projectile
 * @param speed vitesse du projectile
 * @param size taille du projectile
 * @param dmg dégâts infligés
 * @param pos position initiale
 * @param dir direction en degrés
 * @param lifeTime durée de vie du projectile
 * @param indice type de projectile (BASIC, EXPLOSIF, etc.)
 */
void InitBullet(bullet_t * bullet, int speed, int size, int dmg, Vector2 Pos, int dir, float lifeTime, int indice);

/**
 * @brief Met à jour un projectile
 *
 * Gère le mouvement, les effets spéciaux et la désactivation
 * selon le type de projectile.
 *
 * @param bullet pointeur vers le projectile
 */
void UpdateBullet(bullet_t * bullet);

/**
 * @brief Affiche une explosion de projectile explosif
 *
 * @param bullet projectile concerné
 */
void DrawExplosion(bullet_t * bullet);

/**
 * @brief Dessine un projectile
 *
 * @param bullet pointeur vers le projectile
 * @param posJoueur position du joueur (utile pour le rayon)
 */
void DrawBullet(bullet_t * bullet, Vector2 posJoueur);

#endif

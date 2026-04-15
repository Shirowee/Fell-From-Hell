/**
 * @file BulletPool.h
 * @brief Gestion des pools de projectiles (bullets)
 * @author A. Pocholle
 * 
 * Implémente un système de gestion de projectiles basé sur le principe
 * d’object pooling.
 * 
 * Au lieu d’allouer/libérer dynamiquement des projectiles à chaque tir,
 * un tableau de bullets est pré-alloué et réutilisé grâce à un flag
 * d’activité.
 * 
 * Deux pools globaux sont utilisés :
 * - bulletPool : projectiles ennemis
 * - playerBulletPool : projectiles du joueur
 */

#ifndef BULLETPOOL_H
#define BULLETPOOL_H

#include "../../raylib/include/raylib.h"
#include "Projectiles.h"

/**
 * @brief Représente un pool de projectiles (object pool)
 * 
 * Cette structure permet de gérer un ensemble de bullets pré-allouées
 * afin d'éviter les allocations dynamiques répétées pendant l'exécution.
 * 
 * Le pool fonctionne en réutilisant les bullets inactives.
 */
typedef struct bulletPool_s {
    bullet_t* tab; //liste contenant les bullets
    int active; //booléen pour l'activité de la pool
    int nbBulletsActive; //nombre de projectiles actives
    int capacity; //nombre d'elements
} bulletPool_t;

/**
 * @brief Initialise un pool de projectiles
 * 
 * Alloue un tableau de bullets et initialise chaque élément comme inactif.
 * 
 * @param pool pointeur vers le pool à initialiser
 * @param capacity nombre maximum de projectiles dans le pool
 */
void InitBulletPool(bulletPool_t* pool, int capacity);

/**
 * @brief Fait apparaître un projectile dans le pool
 * 
 * Recherche la première bullet inactive afin de la réutiliser.
 * Si aucune bullet n'est disponible, aucun projectile n'est créé.
 * 
 * @param pool pointeur vers le pool
 * @param pos position initiale du projectile
 * @param dir direction (en degrés)
 * @param speed vitesse du projectile
 * @param size taille du projectile
 * @param dmg dégâts infligés
 * @param lifeTime durée de vie du projectile
 * @param indice identifiant ou type de projectile
 */
void SpawnBulletPool(bulletPool_t* pool, Vector2 pos, int dir, int speed, int size, int dmg, float lifeTime, int indice);

/**
 * @brief Met à jour tous les projectiles du pool
 * 
 * Appelle la fonction de mise à jour individuelle pour chaque bullet.
 * 
 * @param pool pointeur vers le pool
 */
void UpdateBulletPool(bulletPool_t* pool);

/**
 * @brief Dessine tous les projectiles du pool
 * 
 * @param pool pointeur vers le pool
 * @param posJoueur position du joueur
 */
void DrawBulletPool(bulletPool_t* pool);

/**
 * @brief Libère la mémoire du pool
 * 
 * Libère le tableau de bullets et réinitialise le pool.
 * 
 * @param pool pointeur vers le pool
 */
void FreeBulletPool(bulletPool_t* pool);


/**
 * @brief Desactive toute les bullets de la pool
 *
 * Desactive toute les bullets de la pool en parcourant le tableau de bullets
 * 
 * @param pool pointeur vers le pool
 */
void DesactAllBullet(bulletPool_t *pool);

/** @brief Pool de projectiles des ennemis */
extern bulletPool_t bulletPool;
/** @brief Pool de projectiles du joueur */
extern bulletPool_t playerBulletPool;
#endif
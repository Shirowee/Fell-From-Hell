/**
 * @file BulletPool.c
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

#include "../../raylib/include/raylib.h"
#include "../../lib/systems/BulletPool.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

bulletPool_t bulletPool; 
bulletPool_t playerBulletPool;

void InitBulletPool(bulletPool_t* pool, int capacity) {
    pool->active = 1;
    pool->capacity = capacity;
    pool->tab = malloc(sizeof(bullet_t) * capacity);

    for(int i = 0; i < capacity;i++){
        pool->tab[i].active = 0;
    }
}

void SpawnBulletPool(bulletPool_t* pool, Vector2 pos, int dir, int speed, int size, int dmg, float lifeTime, int indice) {
    //on cherche la premiere bullet inactive (disponible)
    int spawned = 0;
    for(int i=0; (i < pool->capacity) && (spawned == 0); i++) {
        
        if (pool->tab[i].active == 0) {
            InitBullet(&pool->tab[i], speed, size, dmg, pos, dir, lifeTime, indice);
            spawned = 1;
        }
    }
}

void UpdateBulletPool(bulletPool_t* pool) {
    for(int i=0; i < pool->capacity; i++) {
        UpdateBullet(&pool->tab[i]);
    }
}

void DrawBulletPool(bulletPool_t* pool, Vector2 posJoueur) {
    for(int i=0; i < pool->capacity; i++) {
        DrawBullet(&pool->tab[i], posJoueur);
    }
}

void FreeBulletPool(bulletPool_t* pool) {
    free(pool->tab);
    pool->tab = NULL;
    pool->capacity = 0;
}
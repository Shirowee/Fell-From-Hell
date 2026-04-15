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
    pool->nbBulletsActive = 0;
    pool->capacity = capacity;
    pool->tab = malloc(sizeof(bullet_t) * capacity);

    for(int i = 0; i < capacity;i++){
        pool->tab[i].active = 0;
    }
}

void SpawnBulletPool(bulletPool_t* pool, Vector2 pos, int dir, int speed, int size, int dmg, float lifeTime, int indice) {
    if(pool->nbBulletsActive == pool->capacity){
        fprintf(stderr, "SpawnBulletPool: Erreur: Pool saturé!\n");
        exit(1);
    }
    InitBullet(&pool->tab[pool->nbBulletsActive], speed, size, dmg, pos, dir, lifeTime, indice);
    pool->nbBulletsActive++;
}

void UpdateBulletPool(bulletPool_t* pool) {
    bool desactivated;

    for(int i=0; i < pool->nbBulletsActive; i++) {
        desactivated = false;
        UpdateBullet(&pool->tab[i], pool, &desactivated);
        if(desactivated)
            i--;
    }
}

void DrawBulletPool(bulletPool_t* pool, Vector2 posJoueur) {
    for(int i=0; i < pool->nbBulletsActive; i++) {
        DrawBullet(&pool->tab[i]);
    }
}

void FreeBulletPool(bulletPool_t* pool) {
    free(pool->tab);
    pool->tab = NULL;
    pool->capacity = 0;
}

void DesactAllBullet(bulletPool_t *pool){
    for(int i=0; i < pool->nbBulletsActive; i++) {
        pool->tab[i].active = 0;
    }
    pool->nbBulletsActive = 0;
}
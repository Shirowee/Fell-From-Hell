/**
 * @file EnemyPool.c
 * @brief Gestion du pool d'ennemis (object pooling)
 * @author A. Pocholle
 * 
 * Implémente un système de pool d'ennemis basé sur
 * l’object pooling.
 * 
 * Les ennemis sont pré-alloués dans un tableau et réutilisés
 * via un flag "active", évitant les allocations dynamiques
 * répétées en jeu.
 * 
 * Fonctionnalités :
 * - Initialisation du pool
 * - Spawn d’ennemis
 * - Mise à jour des ennemis
 * - Affichage des ennemis
 * - Libération mémoire
 */
 
#include "../../raylib/include/raylib.h"
#include "../../lib/enemies/EnemyController.h"
#include "../../lib/systems/EnemyPool.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

enemyPool_t enemyPool; 

void InitEnemyPool(enemyPool_t* pool, int capacity) {
    pool->active = 1;
    pool->capacity = capacity;
    pool->tab = malloc(sizeof(enemy_t) * capacity);

    for(int i = 0; i < capacity;i++){
        pool->tab[i].active = 0;
    }
}

void SpawnEnemyPool(enemyPool_t* pool, Vector2 pos, int hp, 
                    float speed, Vector2 size, int dmg, float bulletSpeed, int bulletSize, EnemyType_t type) {
    //on cherche la premiere bullet inactive (disponible)
    int spawned = 0;
    for(int i=0; (i < pool->capacity) && (spawned == 0); i++) {
        
        if (pool->tab[i].active == 0) {
            EnemyInit(&pool->tab[i], hp, speed, size, dmg, pos, bulletSpeed, bulletSize, type);
            spawned = 1;
        }
    }
}

void UpdateEnemyPool(enemyPool_t* pool, Vector2 playerPos) {
    for(int i=0; i < pool->capacity; i++) {
        EnemyUpdate(&pool->tab[i], playerPos);
    }
}

void DrawEnemyPool(enemyPool_t* pool, Vector2 playerPos) {
    for(int i=0; i < pool->capacity; i++) {
        EnemyDraw(&pool->tab[i], playerPos);
    }
}

void FreeEnemyPool(enemyPool_t* pool) {
    free(pool->tab);
    pool->tab = NULL;
    pool->capacity = 0;
}
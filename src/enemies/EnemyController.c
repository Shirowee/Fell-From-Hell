/**
 * @file EnemyController.h
 * @brief Gestion des ennemis et de leur comportement (state machine)
 * 
 * Définit l’interface de contrôle des ennemis du jeu.
 * Implémente une machine à états permettant de gérer différents
 * comportements tels que :
 * - déplacement aléatoire
 * - poursuite du joueur
 * - attaque
 * - états passifs ou inactifs
 *
 * Chaque ennemi est représenté par une structure 'enemy_t' et peut
 * évoluer dynamiquement selon son état interne.
 *
 * Fournit également des fonctions de :
 * - initialisation des ennemis
 * - mise à jour des comportements
 * - gestion des transitions d’états
 * - rendu graphique
 *
 *
 * @author A. Pocholle
 */


#include "../../lib/enemies/EnemyController.h"
#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/systems/BulletPool.h"
#include "../../lib/systems/EnemyPool.h"
#include "../../lib/enemies/EnemyStates.h"
#include "../../raylib/include/raylib.h"
#include <stdio.h>




void EnemyInit(enemy_t * enemy, int hp, float speed, Vector2 size, int dmg,
                Vector2 pos, int bulletSpeed, int bulletSize, EnemyType_t type) {
    /*=================== STATS ===================*/
    enemy->hp = hp;
    enemy->speed = speed;
    enemy->pos = pos;
    enemy->dmg = dmg;
    enemy->size = size;
    enemy->dir = 0;

    /*=================== Bullet related ===================*/

    enemy->bulletSpeed = bulletSpeed;
    enemy->bulletSize = bulletSize;

    /*=================== States related ===================*/
    enemy->stateTimer = 0;
    enemy->state = EnemyState_Idle;
    enemy->type = type;

    /*=================== Logic ===================*/
    enemy->active = 1;
    enemy->isShooting = 0;
}

//deprecated
void EnemyShoots(enemy_t * enemy)
{
    enemy->isShooting = 1;
}


void EnemyUpdate(enemy_t * enemy, Vector2 playerPos)
{
    if ( enemy->active == 0 ) return;
    
    enemy->state(enemy,&bulletPool, playerPos);
    if (enemy->isShooting == 1){
        enemy->isShooting = 0;
        SpawnBulletPool(&bulletPool,enemy->pos,enemy->dir,enemy->bulletSpeed,enemy->bulletSize,enemy->dmg, 100, 0);
    }
}

void CopyEnemy(enemy_t *src, enemy_t *dest, bool cut){
    dest->active = src->active;
    dest->bulletSize = src->bulletSize;
    dest->bulletSpeed = src->bulletSpeed;
    dest->dir = src->dir;
    dest->dmg = src->dmg;
    dest->hp = src->hp;
    dest->isShooting = src->isShooting;
    dest->pos = src->pos;
    dest->size = src->size;
    dest->speed = src->speed;
    dest->state = src->state;
    dest->stateTimer = src->stateTimer;
    dest->type = src->type;

    if(cut)
        src->active = 0;
}

void DesactivateEnemy(enemy_t *enemy, enemyPool_t *originPool){
    //Remplace le projectile à désactiver par le dernier projectile actif
    CopyEnemy(&originPool->tab[originPool->nbEnemiesActive-1], enemy, true);
    originPool->nbEnemiesActive--;
}


void EnemyDraw(enemy_t * enemy)
{
    if (enemy->active == 0) return;
    float centered_x = enemy->pos.x - enemy->size.x / 2;
    float centered_y = enemy->pos.y - enemy->size.y / 2;
    DrawRectangleV((Vector2){centered_x, centered_y}, enemy->size, RED);
}

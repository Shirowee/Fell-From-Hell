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
#include "../../lib/enemies/EnemyStates.h"
#include "../../raylib/include/raylib.h"




void EnemyInit(enemy_t * enemy, float speed, Vector2 size, int dmg,
                Vector2 pos, int bulletSpeed, int bulletSize) {
    enemy->speed = speed;
    enemy->pos = pos;
    enemy->dmg = dmg;
    enemy->isShooting = 0;
    enemy->size = size;
    enemy->dir = 0;
    enemy->bulletSpeed = bulletSpeed;
    enemy->bulletSize = bulletSize;
    enemy->active = 1;

    enemy->stateTimer = 0;
    enemy->state = EnemyState_Idle;
    enemy->type = GetRandomValue(0, 2);
}


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


void EnemyDraw(enemy_t * enemy)
{
    if (enemy->active == 0) return;
    float centered_x = enemy->pos.x - enemy->size.x / 2;
    float centered_y = enemy->pos.y - enemy->size.y / 2;
    DrawRectangleV((Vector2){centered_x, centered_y}, enemy->size, RED);
}

/**
 * @file EnemyStates.h
 * @brief Machine à états des ennemis
 *
 * Définit la machine à états utilisée pour contrôler
 * le comportement des ennemis dans le jeu.
 *
 * Chaque ennemi possède un état courant qui détermine son comportement,
 * par exemple :
 * - état de base (idle)
 * - déplacement (move)
 * - poursuite du joueur (chase)
 * - attaque (attack)
 *
 * Les transitions entre états sont gérées en fonction de conditions
 * internes (distance au joueur, timer, dégâts, etc.).
 *
 *
 * @author A. Pocholle
 */

#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/enemies/EnemyController.h"
#include "../../lib/enemies/EnemyStates.h"
#include "../../lib/systems/BulletPool.h"
#include "../../raylib/include/raylib.h"
#include <stdio.h>
/*
* STATES MACHINE
*/
void EnemyState_Idle(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos){
    enemy->stateTimer += GetFrameTime();
    int randomValue;
    if (enemy->stateTimer > 0.1f){
        switch (enemy->type)
            {
            case ENEMY_CHASER:
                enemy->state = EnemyState_MoveTowardsPlayer;
                break;

            case ENEMY_SHOOTER_CIRCLE:
                randomValue = GetRandomValue(0, 100);
                if (randomValue <= 60) {
                    enemy->state = EnemyState_EnemyShootCircle;
                }
                else {
                    enemy->state = EnemyState_MoveRandom;
                }
                
                break;
            case ENEMY_SHOOTER:
                randomValue = GetRandomValue(0, 100);
                if (randomValue <= 60) {
                    enemy->state = EnemyState_EnemyShoot;
                }
                else {
                    enemy->state = EnemyState_MoveRandom;
                }
                break;
            }
        enemy->stateTimer = 0;
    }
}


/*
*MOVEMENTS
 */
void EnemyState_MoveTowardsPlayer(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos){
    EnemyMoveTowardsPlayer(enemy, playerPos);
}

void EnemyState_MoveRandom(enemy_t * enemy, bulletPool_t* pool, Vector2 playerPos)
{
    float dt = GetFrameTime();
    enemy->stateTimer += dt;

    //change direction toutes les 1 seconde
    if ((int)(enemy->stateTimer) != (int)(enemy->stateTimer - dt))
    {
        enemy->dir = GetRandomValue(0, 360);
    }

    //mouvement continu
    EnemyMove(enemy);

    //quitter après 3 secondes
    if (enemy->stateTimer > 3.0f)
    {
        enemy->state = EnemyState_Idle;
        enemy->stateTimer = 0;
    }
}


void EnemyState_EnemyShootCircle(enemy_t* enemy, bulletPool_t* pool, Vector2 playerPos)
{

    float dt = GetFrameTime();
    enemy->stateTimer += dt;
    if (enemy->stateTimer > 0.5f) {
        int bullets = 8;

        for (int i = 0; i < bullets; i++)
        {
            float angle = (360.0f / bullets) * i;
            SpawnBulletPool(pool,
                enemy->pos,
                angle,
                enemy->bulletSpeed,
                enemy->bulletSize,
                enemy->dmg,
                100,
                0);
            
        }
        enemy->state = EnemyState_Idle;
    }
}

void EnemyState_EnemyShoot(enemy_t* enemy, bulletPool_t* pool, Vector2 playerPos)
{
    EnemySetDirTowardsPlayer(enemy, playerPos);
    EnemyShoots(enemy);
    enemy->state = EnemyState_Idle;
}

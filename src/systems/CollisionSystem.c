/**
 * @file CollisionSystem.c
 * @brief Gestion des collisions entre ennemis et projectiles
 * @author A. Pocholle
 * 
 * Implémente la détection de collision entre les ennemis
 * et les bullets à l’aide d’une méthode simple basée sur la distance
 * entre deux points (collision circulaire).
 * 
 * Lorsqu'une collision est détectée :
 * - l'ennemi est désactivé
 * - la bullet est désactivée
 */


#include "../../raylib/include/raylib.h"
#include "../../lib/systems/CollisionSystem.h"
#include "../../lib/player/Player.h"
#include "../../lib/systems/LifeManager.h"
#include <math.h>

#define MAX_DIST_DETECT 200

void CheckEnemyBulletCollision(enemyPool_t* enemies, bulletPool_t* bullets)
{
    int total_dmg;
    enemy_t* enemy;
    bullet_t* bullet;
    float dx;
    float dy;
    float dist, distMin;
    int i, j;


    for (i = 0; i < enemies->capacity; i++)
    {
        total_dmg = 0;
        enemy = &enemies->tab[i];
        if (!enemy->active) continue;

        for (j = 0; j < bullets->capacity; j++)
        {
            bullet = &bullets->tab[j];
            if (!bullet->active) continue;
            //Ne vérifie que pour les plateformes les plus proches
            if(bullet->bulletPos.x + bullet->bulletSize < enemy->pos.x - MAX_DIST_DETECT || 
                bullet->bulletPos.x > enemy->pos.x + MAX_DIST_DETECT) continue;
            if(bullet->bulletPos.y + bullet->bulletSize < enemy->pos.y - MAX_DIST_DETECT ||
                bullet->bulletPos.y > enemy->pos.y + MAX_DIST_DETECT) continue;

            dx = enemy->pos.x - bullet->bulletPos.x;
            dy = enemy->pos.y - bullet->bulletPos.y;

            dist = dx * dx + dy * dy;
            distMin = (enemy->size.x * 0.5f + bullet->bulletSize)*(enemy->size.x * 0.5f + bullet->bulletSize);

            if (dist < distMin)
            {
                bullet->active = 0;
                total_dmg += bullet->bulletDmg;
            }
        }

        ApplyDamageToEnemy(enemy, total_dmg);

        if(enemy->hp <= 0.0)
            enemy->active = 0;
    }
}

void CheckPlayerEnemyCollision(Player* player, enemyPool_t* enemies, int* total_dmg){
    int i;
    int gap = 0.05; //En %
    enemy_t* enemy;
    Rectangle playerHitbox = (Rectangle){
        player->position.x + (int)(player->size.x*gap),
        player->position.y + (int)(player->size.y*gap),
        player->size.x - (int)(2*player->size.x*gap),
        player->size.y - (int)(2*player->size.y*gap)
    };
    Rectangle enemyHitbox;

    //Vérification des collision
    for(i = 0; i < enemies->capacity; i++){
        enemy = &enemies->tab[i];

        if(enemy->pos.x + enemy->size.x < player->position.x - PLAYER_MAX_DIST_DETECT) continue;
        if(enemy->pos.x > player->position.x + PLAYER_MAX_DIST_DETECT) continue;
        if(enemy->pos.y + enemy->size.y < player->position.y - PLAYER_MAX_DIST_DETECT) continue;
        if(enemy->pos.y > player->position.y + PLAYER_MAX_DIST_DETECT) continue;

        if(enemy->active){
            //Initialisation de la hitbox de l'ennemie
            enemyHitbox.x = enemy->pos.x + (int)(enemy->size.x*gap);
            enemyHitbox.y = enemy->pos.y + (int)(enemy->size.y*gap);
            enemyHitbox.width = enemy->size.x - (int)(2*enemy->size.x*gap);
            enemyHitbox.height = enemy->size.y - (int)(2*enemy->size.y*gap);

            if(CheckCollisionRecs(playerHitbox, enemyHitbox))
                *total_dmg += enemy->dmg;
        }
    }
}

void CheckPlayerBulletCollision(Player* player, bulletPool_t* bullets, int* total_dmg){
    int i;
    bullet_t* bullet;

    //Vérification des collision
    for(i = 0; i < bullets->capacity; i++){
        bullet = &bullets->tab[i];

        if(bullet->active){
            float dx = player->position.x - bullet->bulletPos.x;
            float dy = player->position.y - bullet->bulletPos.y;

            float dist = sqrtf(dx * dx + dy * dy);

            if (dist < (player->size.x * 0.5f + bullet->bulletSize))
            {
                *total_dmg += bullet->bulletDmg;
                bullet->active = 0;
            }
        }
    }
}
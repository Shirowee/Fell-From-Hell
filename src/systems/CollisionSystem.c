/**
 * @file CollisionSystem.c
 * @brief Gestion des collisions entre ennemis et projectiles
 * @author A. Pocholle, C. Tortevoix
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
#include "../../lib/systems/Projectiles.h"
#include <math.h>
#include <stdio.h>

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

        for (j = 0; j < bullets->nbBulletsActive; j++)
        {
            bullet = &bullets->tab[j];
            if (!bullet->active) continue;
            //Ne vérifie que pour les plateformes les plus proches
            if(bullet->indice != RAYON){
                if(bullet->bulletPos.x + bullet->bulletSize < enemy->pos.x - MAX_DIST_DETECT || 
                    bullet->bulletPos.x > enemy->pos.x + MAX_DIST_DETECT) continue;
                if(bullet->bulletPos.y + bullet->bulletSize < enemy->pos.y - MAX_DIST_DETECT ||
                    bullet->bulletPos.y > enemy->pos.y + MAX_DIST_DETECT) continue;
            }

            //cas du laser
            if (bullet->indice == RAYON) {
                Vector2 A = bullet->laserPos;   // début du laser
                Vector2 B = bullet->bulletPos;  // fin du laser
                Vector2 P = enemy->pos;         // centre ennemi

                // vecteurs
                float ABx = B.x - A.x;
                float ABy = B.y - A.y;
                float APx = P.x - A.x;
                float APy = P.y - A.y;

                float ab2 = ABx * ABx + ABy * ABy;
                float t = (APx * ABx + APy * ABy) / ab2;

                // clamp entre 0 et 1
                if (t < 0) t = 0;
                if (t > 1) t = 1;

                // point le plus proche sur le segment
                float closestX = A.x + ABx * t;
                float closestY = A.y + ABy * t;

                float dx = P.x - closestX;
                float dy = P.y - closestY;

                float dist = dx * dx + dy * dy;

                float radius = enemy->size.x * 0.5f + bullet->bulletSize * 0.5f;

                if (dist < radius * radius) {
                    total_dmg += bullet->bulletDmg;
                    bullet->bulletSize *= 0.7;  //diminution de 30%
                    if(bullet->bulletSize <= 1.0)
                        bullet->active=0;   //verifier si desactive bien !!
                }

                continue;
            }

            dx = enemy->pos.x - bullet->bulletPos.x;
            dy = enemy->pos.y - bullet->bulletPos.y;

            dist = dx * dx + dy * dy;
            distMin = (enemy->size.x * 0.5f + bullet->bulletSize)*(enemy->size.x * 0.5f + bullet->bulletSize);

            if (dist < distMin)
            {
                //cas explosif
                if (bullet->indice == EXPLOSIF) {
                    //DrawExplosion(bullet); //marche pas (dessin écrasé par les autre draw je crois)
                    float explosionRadius = bullet->bulletSize*20; //const à revoir

                    for (int k = 0; k < enemies->capacity; k++) {
                        enemy_t *e = &enemies->tab[k];
                        if (!e->active) continue;

                        float dx = e->pos.x - bullet->bulletPos.x;
                        float dy = e->pos.y - bullet->bulletPos.y;

                        float dist2 = dx * dx + dy * dy;

                        float enemyRadius = e->size.x * 0.5f;
                        float radiusSum = explosionRadius + enemyRadius;
                        float radiusSum2 = radiusSum * radiusSum;

                        if (dist2 < radiusSum2) {

                            float dist = sqrtf(dist2);

                            float t = dist / explosionRadius;
                            if (t > 1.0f) t = 1.0f;

                            float damageFactor = 1.0f - (t * t);

                            if (damageFactor < 0.0f) damageFactor = 0.0f;

                            ApplyDamageToEnemy(e, bullet->bulletDmg * damageFactor);
                            if(e->hp <= 0.0)
                                e->active = 0;
                        }
                    }

                } else {
                    total_dmg += bullet->bulletDmg;
                }

                DesactivateBullet(bullet, bullets);
                j--;

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
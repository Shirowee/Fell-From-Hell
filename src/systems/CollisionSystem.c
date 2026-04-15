/**
 * @file CollisionSystem.c
 * @brief Gestion des collisions entre ennemis et projectiles
 * @author A. Pocholle, C. Tortevoix
 * 
 * Implémente la détection de collision entre les ennemis,
 * les projectiles, le joueur et les plateformes
 */


#include "../../raylib/include/raylib.h"
#include "../../lib/systems/CollisionSystem.h"
#include "../../lib/player/Player.h"
#include "../../lib/systems/LifeManager.h"
#include "../../lib/systems/Projectiles.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIST_DETECT 200

void CheckEnemyBulletCollision(enemyPool_t* enemies, bulletPool_t* bullets){
    int i, j;
    int total_dmg;
    float gap = 0.05; //En %
    enemy_t* enemy;
    bullet_t* bullet;
    Rectangle enemyHitbox;

    for (i = 0; i < enemies->capacity; i++){
        total_dmg = 0;
        enemy = &enemies->tab[i];

        if (!enemy->active) continue;

        //Initialisation de la hitbox de l'ennemie
        enemyHitbox.x = enemy->pos.x + (int)(enemy->size.x*gap);
        enemyHitbox.y = enemy->pos.y + (int)(enemy->size.y*gap);
        enemyHitbox.width = enemy->size.x - (int)(2*enemy->size.x*gap);
        enemyHitbox.height = enemy->size.y - (int)(2*enemy->size.y*gap);

        //Vérification des collision
        for(j = 0; j < bullets->capacity; j++){
            bullet = &bullets->tab[j];

            if (!bullet->active) continue;
            //Ne vérifie que pour les plateformes les plus proches
            if(bullet->indice != RAYON){
                if(bullet->bulletPos.x + bullet->bulletSize < enemy->pos.x - MAX_DIST_DETECT || 
                    bullet->bulletPos.x > enemy->pos.x + enemy->size.x + MAX_DIST_DETECT) continue;
                if(bullet->bulletPos.y + bullet->bulletSize < enemy->pos.y - MAX_DIST_DETECT ||
                    bullet->bulletPos.y > enemy->pos.y + enemy->size.y + MAX_DIST_DETECT) continue;
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

            if(CheckCollisionCircleRec(bullet->bulletPos, bullet->bulletSize, enemyHitbox)){
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
    float gap = 0.05; //En %
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

        if(!enemy->active) continue;

        if(enemy->pos.x + enemy->size.x < player->position.x - PLAYER_MAX_DIST_DETECT) continue;
        if(enemy->pos.x > player->position.x + PLAYER_MAX_DIST_DETECT) continue;
        if(enemy->pos.y + enemy->size.y < player->position.y - PLAYER_MAX_DIST_DETECT) continue;
        if(enemy->pos.y > player->position.y + PLAYER_MAX_DIST_DETECT) continue;

        //Initialisation de la hitbox de l'ennemie
        enemyHitbox.x = enemy->pos.x + (int)(enemy->size.x*gap);
        enemyHitbox.y = enemy->pos.y + (int)(enemy->size.y*gap);
        enemyHitbox.width = enemy->size.x - (int)(2*enemy->size.x*gap);
        enemyHitbox.height = enemy->size.y - (int)(2*enemy->size.y*gap);

        if(CheckCollisionRecs(playerHitbox, enemyHitbox))
            *total_dmg += enemy->dmg;
    }
}

void CheckPlayerBulletCollision(Player* player, bulletPool_t* bullets, int* total_dmg){
    int i;
    float gap = 0.05; //En %
    bullet_t* bullet;
    Rectangle playerHitbox = (Rectangle){
        player->position.x + (int)(player->size.x*gap),
        player->position.y + (int)(player->size.y*gap),
        player->size.x - (int)(2*player->size.x*gap),
        player->size.y - (int)(2*player->size.y*gap)
    };

    //Vérification des collision
    for(i = 0; i < bullets->capacity; i++){
        bullet = &bullets->tab[i];

        if (!bullet->active) continue;
        //Ne vérifie que pour les plateformes les plus proches
        if(bullet->bulletPos.x + bullet->bulletSize < player->position.x - MAX_DIST_DETECT || 
            bullet->bulletPos.x > player->position.x + player->size.x + MAX_DIST_DETECT) continue;
        if(bullet->bulletPos.y + bullet->bulletSize < player->position.y - MAX_DIST_DETECT ||
            bullet->bulletPos.y > player->position.y + player->size.y + MAX_DIST_DETECT) continue;

        if(CheckCollisionCircleRec(bullet->bulletPos, bullet->bulletSize, playerHitbox)){
            *total_dmg += bullet->bulletDmg;
            DesactivateBullet(bullet, bullets);
            i--;
        }
    }

}

void CheckBulletsPlatformsCollision(bulletPool_t *bullets, Platform platforms[], const int nbPlatforms){
    bullet_t *bullet;
    Platform *platform;
    int i, j;

    for (i = 0; i < nbPlatforms; i++){
        platform = &platforms[i];
        for (j = 0; j < bullets->nbBulletsActive; j++){
            bullet = &bullets->tab[j];
            if(!bullet->active) continue;
            //Ne vérifie que pour les plateformes les plus proches
            if(bullet->bulletPos.x + bullet->bulletSize < platform->x - MAX_DIST_DETECT || 
                bullet->bulletPos.x > platform->x + platform->width + MAX_DIST_DETECT) continue;
            if(bullet->bulletPos.y + bullet->bulletSize < platform->y - MAX_DIST_DETECT ||
                bullet->bulletPos.y > platform->y + platform->high + MAX_DIST_DETECT) continue;

            if (platform->solid || (bullet->bulletDir > 0 && bullet->bulletDir < 180)) {
                if(CheckCollisionCircleRec(bullet->bulletPos, bullet->bulletSize, platform->rect)){
                    DesactivateBullet(bullet, bullets);
                    j--;
                }
            }
        }
    }
}

// Correction de la position du joueur en cas de collision avec les plateformes
void PlayerPositionFix(Player *player, Vector2 oldPosition, Platform platforms[], const int nbPlatforms){
    int i;
    int distanceX, distanceY;
    int platformCenterX, platformCenterY;
    int playerCenterX, playerCenterY;

    float prevBottom;
    float currBottom;
    float platformTop;

    bool collision;
    bool wasAbove;
    bool isFalling = player->velocity.y > 0;

    MovementState state = getPlayerMovementState(player);
    Rectangle body = (Rectangle){player->position.x, player->position.y, player->size.x, player->size.y};

    for(i = 0; i < nbPlatforms; i++) {
        //Ne vérifie que pour les plateformes les plus proches
        if(platforms[i].x + platforms[i].width < player->position.x - PLAYER_MAX_DIST_DETECT || 
            platforms[i].x > player->position.x + PLAYER_MAX_DIST_DETECT) continue;
        if(platforms[i].y + platforms[i].high < player->position.y - PLAYER_MAX_DIST_DETECT ||
            platforms[i].y > player->position.y + PLAYER_MAX_DIST_DETECT) continue;


        collision = false;
        // Calcul du centre de la plateforme
        platformCenterX = platforms[i].x + platforms[i].width / 2;
        platformCenterY = platforms[i].y + platforms[i].high / 2;

        if(platforms[i].solid) {
            if(CheckCollisionRecs(body, platforms[i].rect)){
                collision = true;
                // Calcul du centre de la rectangle main
                playerCenterX = player->position.x + player->size.x / 2;
                playerCenterY = player->position.y + player->size.y / 2;

                // Calcul de la distance entre le joueur et la plateforme
                distanceX = (player->size.x / 2 + platforms[i].width / 2) - abs(playerCenterX - platformCenterX);
                distanceY = (player->size.y / 2 + platforms[i].high / 2) - abs(playerCenterY - platformCenterY);

                if(distanceX < distanceY) { // Collision sur l'axe x
                    if (playerCenterX < platformCenterX) {
                        player->position.x = platforms[i].x - player->size.x; // Collision à droite
                        if(state == JUMPING || state == FALLING){
                            player->movConfig.isOnLeftWall = false;
                            player->movConfig.isOnRightWall = true;
                            player->velocity.y = 0;
                        }
                    } else {
                        player->position.x = platforms[i].x + platforms[i].width; // Collision à gauche
                        if(state == JUMPING || state == FALLING){
                            player->movConfig.isOnLeftWall = true;
                            player->movConfig.isOnRightWall = false;
                            player->velocity.y = 0;
                        }
                    }
                    player->velocity.x = 0; // Arrêter le mouvement horizontal
                    if(state == DASHING)
                        player->movConfig.isDashing = false;
                }
                else { // Collision sur l'axe y
                    if (playerCenterY < platformCenterY) {
                        player->position.y = platforms[i].y - player->size.y; // Collision en bas
                        if (state == FALLING) {
                            player->movConfig.isOnGround = true;
                            player->velocity.y = 0; // Arrêter le mouvement vertical
                        }
                        if (state == WALL_SLIDING) {
                            player->movConfig.isOnGround = true;
                            player->movConfig.isOnLeftWall = false;
                            player->movConfig.isOnRightWall = false;
                            player->velocity.y = 0;
                        }
                    } 
                    else {
                        player->position.y = platforms[i].y + platforms[i].high; // Collision en haut
                        if (state == JUMPING) {
                            player->velocity.y = 0; // Arrêter le mouvement vertical
                        }
                        if(state == DASHING)
                            player->movConfig.isDashing = false;
                    }
                }
            }
        }
        else {
            prevBottom = oldPosition.y + player->size.y;
            currBottom = player->position.y + player->size.y;
            platformTop = platforms[i].y;

            wasAbove = prevBottom <= platformTop;

            if(wasAbove && isFalling && currBottom >= platformTop && CheckCollisionRecs(body, platforms[i].rect)){
                player->position.y = platforms[i].y - player->size.y; // Collision en bas
                player->velocity.y = 0; // Arrêter le mouvement vertical
                player->movConfig.isOnGround = true;
                collision = true;
                if (state == WALL_SLIDING) {
                    player->movConfig.isOnLeftWall = false;
                    player->movConfig.isOnRightWall = false;
                    player->velocity.y = 0;
                }
            }
        }

        if(collision){
            // Mettre à jour le corps du joueur après correction de position
            body.x = player->position.x;
            body.y = player->position.y;
        }
    }
}

/*
void EnemiesPositionFix(enemyPool_t *enemies, Platform platform[], const int nbPlatforms){
    int i, j;
    int distanceX, distanceY;
    int platformCenterX, platformCenterY;
    int enemyCenterX, enemyCenterY;

    float prevBottom;
    float currBottom;
    float platformTop;

    bool collision;
    bool wasAbove;
    bool isFalling;

    enemy_t *enemy;
    Rectangle enemyBody;

    for(i = 0; i < enemies->capacity; i++){
        enemy = &enemies->tab[i];

        enemy->type = 

        //Initialisation de la boîte de collision de l'ennemi
        enemyBody.x = enemy->pos.x;
        enemyBody.y = enemy->pos.y;
        enemyBody.width = enemy->size.x;
        enemyBody.height = enemy->size.y;

        for(j = 0; j < nbPlatforms; j++) {
            //Ne vérifie que pour les plateformes les plus proches
            if(platform[i].x + platform[i].width < player->position.x - PLAYER_MAX_DIST_DETECT || 
                platform[i].x > player->position.x + PLAYER_MAX_DIST_DETECT) continue;
            if(platform[i].y + platform[i].high < player->position.y - PLAYER_MAX_DIST_DETECT ||
                platform[i].y > player->position.y + PLAYER_MAX_DIST_DETECT) continue;


            collision = false;
            // Calcul du centre de la plateforme
            platformCenterX = platform[i].x + platform[i].width / 2;
            platformCenterY = platform[i].y + platform[i].high / 2;

            if(platform[i].solid) {
                if(CheckCollisionRecs(body, platform[i].rect)){
                    collision = true;
                    // Calcul du centre de la rectangle main
                    playerCenterX = player->position.x + player->size.x / 2;
                    playerCenterY = player->position.y + player->size.y / 2;

                    // Calcul de la distance entre le joueur et la plateforme
                    distanceX = (player->size.x / 2 + platform[i].width / 2) - abs(playerCenterX - platformCenterX);
                    distanceY = (player->size.y / 2 + platform[i].high / 2) - abs(playerCenterY - platformCenterY);

                    if(distanceX < distanceY) { // Collision sur l'axe x
                        if (playerCenterX < platformCenterX) {
                            player->position.x = platform[i].x - player->size.x; // Collision à droite
                            if(state == JUMPING || state == FALLING){
                                player->movConfig.isOnLeftWall = false;
                                player->movConfig.isOnRightWall = true;
                                player->velocity.y = 0;
                            }
                        } else {
                            player->position.x = platform[i].x + platform[i].width; // Collision à gauche
                            if(state == JUMPING || state == FALLING){
                                player->movConfig.isOnLeftWall = true;
                                player->movConfig.isOnRightWall = false;
                                player->velocity.y = 0;
                            }
                        }
                        player->velocity.x = 0; // Arrêter le mouvement horizontal
                        if(state == DASHING)
                            player->movConfig.isDashing = false;
                    }
                    else { // Collision sur l'axe y
                        if (playerCenterY < platformCenterY) {
                            player->position.y = platform[i].y - player->size.y; // Collision en bas
                            if (state == FALLING) {
                                player->movConfig.isOnGround = true;
                                player->velocity.y = 0; // Arrêter le mouvement vertical
                            }
                            if (state == WALL_SLIDING) {
                                player->movConfig.isOnGround = true;
                                player->movConfig.isOnLeftWall = false;
                                player->movConfig.isOnRightWall = false;
                                player->velocity.y = 0;
                            }
                        } 
                        else {
                            player->position.y = platform[i].y + platform[i].high; // Collision en haut
                            if (state == JUMPING) {
                                player->velocity.y = 0; // Arrêter le mouvement vertical
                            }
                            if(state == DASHING)
                                player->movConfig.isDashing = false;
                        }
                    }
                }
            }
            else {
                prevBottom = oldPosition.y + player->size.y;
                currBottom = player->position.y + player->size.y;
                platformTop = platform[i].y;

                wasAbove = prevBottom <= platformTop;

                if(wasAbove && isFalling && currBottom >= platformTop && CheckCollisionRecs(body, platform[i].rect)){
                    player->position.y = platform[i].y - player->size.y; // Collision en bas
                    player->velocity.y = 0; // Arrêter le mouvement vertical
                    player->movConfig.isOnGround = true;
                    collision = true;
                    if (state == WALL_SLIDING) {
                        player->movConfig.isOnLeftWall = false;
                        player->movConfig.isOnRightWall = false;
                        player->velocity.y = 0;
                    }
                }
            }

            if(collision){
                // Mettre à jour le corps du joueur après correction de position
                body.x = player->position.x;
                body.y = player->position.y;
            }
        }
    }
}*/
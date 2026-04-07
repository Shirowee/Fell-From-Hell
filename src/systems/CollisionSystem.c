#include "../../raylib/include/raylib.h"
#include "../../lib/systems/CollisionSystem.h"
#include "../../lib/player/Player.h"
#include <math.h>

void CheckEnemyBulletCollision(enemyPool_t* enemies, bulletPool_t* bullets)
{
    for (int i = 0; i < enemies->capacity; i++)
    {
        enemy_t* e = &enemies->tab[i];
        if (!e->active) continue;

        for (int j = 0; j < bullets->capacity; j++)
        {
            bullet_t* b = &bullets->tab[j];
            if (!b->active) continue;

            float dx = e->pos.x - b->bulletPos.x;
            float dy = e->pos.y - b->bulletPos.y;

            float dist = sqrtf(dx * dx + dy * dy);

            if (dist < (e->size.x * 0.5f + b->bulletSize))
            {
                e->active = 0;
                b->active = 0;

                break;
            }
        }
    }
}

void checkPlayerEnemyCollision(Player* player, enemyPool_t* enemies, int* total_dmg){
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

void checkPlayerBulletCollision(Player* player, bulletPool_t* bullets, int* total_dmg){
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
            }
        }
    }
}
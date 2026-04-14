/**
 * @file Projectiles.c
 * @brief Gestion des projectiles du jeu
 * @authors A. Pocholle, Kilian
 *
 * Ce module gère la création, la mise à jour et l'affichage
 * des projectiles.
 *
 * Plusieurs types de projectiles sont supportés :
 * - BASIC : projectile classique
 * - EXPLOSIF : projectile avec explosion
 * - RAYON : tir instantané type laser
 * - MELEE : (non implémenté)
 */

#include "../../raylib/include/raylib.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/systems/Projectiles.h"
#include <math.h>
#include <stdio.h> //pour les test printf

void InitBullet(bullet_t * bullet, int speed, int size, int dmg, Vector2 pos, int dir, float lifeTime, int indice) {
    bullet->bulletSpeed = speed;
    bullet->bulletSize = size;
    bullet->bulletDmg = dmg;
    bullet->bulletPos = pos;
    bullet->laserPos = pos;   
    bullet->bulletDir = dir;
    bullet->createTime = GetTime();
    bullet->lifeTime = lifeTime;
    bullet->indice = indice;
    bullet->active = 1;
}

void UpdateBullet(bullet_t *bullet, bulletPool_t *originPool, bool *desactivated) {
    *desactivated = false;

    if (!bullet->active) return;

    float dt = GetFrameTime();
    float angleRad = bullet->bulletDir * DEG2RAD;
    
    switch (bullet->indice){
    case BASIC:
        bullet->bulletPos.x += cosf(angleRad) * bullet->bulletSpeed * dt;
        bullet->bulletPos.y += sinf(angleRad) * bullet->bulletSpeed * dt;

        //vérification que la bullet soit dans l'écran sinon c'est à unload
        if (bullet->bulletPos.x < -50 || bullet->bulletPos.x > currentLevel.info.width+50 || bullet->bulletPos.y < -50 || bullet->bulletPos.y > currentLevel.info.height+50) {
                DesactivateBullet(bullet, originPool);
                *desactivated = true;
        }
        break;

    case EXPLOSIF:
        bullet->bulletPos.x += cosf(angleRad) * bullet->bulletSpeed * dt;
        bullet->bulletPos.y += sinf(angleRad) * bullet->bulletSpeed * dt;

        if(GetTime() - bullet->createTime >= bullet->lifeTime){
            DrawExplosion(bullet);
        }
        break;

    case RAYON:
        bullet->bulletPos.x += cosf(angleRad) * 4000; //constante temp
        bullet->bulletPos.y += sinf(angleRad) * 4000; 
        break;

    case MELEE:
        break;
    }

    //durer de vie dépassée
    if(GetTime() - bullet->createTime >= bullet->lifeTime){
        DesactivateBullet(bullet, originPool);
        *desactivated = true;
    }
}

void CopyBullet(bullet_t *src, bullet_t *dest, bool cut){
    dest->active = src->active;
    dest->bulletDir = src->bulletDir;
    dest->bulletDmg = src->bulletDmg;
    dest->bulletPos = src->bulletPos;
    dest->bulletSize = src->bulletSize;
    dest->bulletSpeed = src->bulletSpeed;
    dest->createTime = src->createTime;
    dest->indice = src->indice;
    dest->lifeTime = src->lifeTime;

    if(cut)
        src->active = 0;
}

void DesactivateBullet(bullet_t *bullet, bulletPool_t *originPool){
    //Remplace le projectile à désactiver par le dernier projectile actif
    CopyBullet(&originPool->tab[originPool->nbBulletsActive-1], bullet, true);
    originPool->nbBulletsActive--;
}

void DrawExplosion(bullet_t * bullet) {
    DrawCircleV(bullet->bulletPos, bullet->bulletSize*5, ORANGE);
}

void DrawBullet(bullet_t * bullet) {
    if (!bullet->active) return;

    switch (bullet->indice)
    {
    case BASIC:
        
        DrawCircleV(bullet->bulletPos, bullet->bulletSize, BLACK);
        break;

    case EXPLOSIF:
        DrawCircleV(bullet->bulletPos, bullet->bulletSize, BLACK);
        break;

    case RAYON:
        DrawLineEx(bullet->laserPos, bullet->bulletPos, bullet->bulletSize, BLACK);
        break;

    case MELEE:
        break;
    }
}

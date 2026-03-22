#include "../../raylib/include/raylib.h"
#include "../../lib/systems/Projectiles.h"
#include <math.h>


void InitBullet(bullet_t * bullet, int speed, int size, int dmg, Vector2 pos, int dir, float lifeTime, int indice) {
    bullet->bulletSpeed = speed;
    bullet->bulletSize = size;
    bullet->bulletDmg = dmg;
    bullet->bulletPos = pos;   
    bullet->bulletDir = dir;
    bullet->createTime = GetTime();
    bullet->lifeTime = lifeTime;
    bullet->indice = indice;
    bullet->active = 1;
}

void UpdateBullet(bullet_t * bullet) {
    if (!bullet->active) return;

    float dt = GetFrameTime();
    float angleRad = bullet->bulletDir * DEG2RAD;
    
    switch (bullet->indice){
    case BASIC:
        bullet->bulletPos.x += cosf(angleRad) * bullet->bulletSpeed * dt;
        bullet->bulletPos.y += sinf(angleRad) * bullet->bulletSpeed * dt;

        //vérification que la bullet soit dans l'écran sinon c'est à unload
        if (bullet->bulletPos.x < -50 || bullet->bulletPos.x > 850 || bullet->bulletPos.y < -50 || bullet->bulletPos.y > 500) {
                bullet->active = false;
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
        bullet->bulletPos.x += cosf(angleRad) * 500; //constante temp
        bullet->bulletPos.y += sinf(angleRad) * 500; 
        break;

    case MELEE:
        break;
    }

    //durer de vie dépassée
    if(GetTime() - bullet->createTime >= bullet->lifeTime){
        bullet->active = false;
    }
}

void DrawExplosion(bullet_t * bullet) {
    DrawCircleV(bullet->bulletPos, 200, ORANGE);
}

void DrawBullet(bullet_t * bullet) {
    if (!bullet->active) return;
    Vector2 posJoueur =(Vector2){400, 200}; //temp

    switch (bullet->indice)
    {
    case BASIC:
        DrawCircleV(bullet->bulletPos, bullet->bulletSize, BLACK);
        break;

    case EXPLOSIF:
        DrawCircleV(bullet->bulletPos, bullet->bulletSize, BLACK);
        break;

    case RAYON:
        DrawLineEx(posJoueur, bullet->bulletPos, bullet->bulletSize, BLACK);
        break;

    case MELEE:
        break;
    }
}

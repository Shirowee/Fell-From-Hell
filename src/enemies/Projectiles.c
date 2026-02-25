#include "../../raylib/include/raylib.h"
#include "../../lib/enemies/Projectiles.h"
#include <math.h>
#include <stdio.h>

void InitBullet(bullet_t * bullet, int speed, int size, int dmg, Vector2 pos, int dir ) {
    bullet->bulletSpeed = speed;
    bullet->bulletSize = size;
    bullet->bulletDmg = dmg;
    bullet->bulletPos = pos;   
    bullet->bulletDir = dir;
    bullet->active = 1;
}

void UpdateBullet(bullet_t * bullet) {
    float dt = GetFrameTime();
    float angleRad = bullet->bulletDir * DEG2RAD;

    bullet->bulletPos.x += cosf(angleRad) * bullet->bulletSpeed * dt;
    bullet->bulletPos.y += sinf(angleRad) * bullet->bulletSpeed * dt;

    //vérification que la bullet soit dans l'écran sinon c'est à unload
    if (bullet->bulletPos.x < -50 || bullet->bulletPos.x > 850 || bullet->bulletPos.y < -50 || bullet->bulletPos.y > 500) {
            bullet->active = false;
    }
}


void DrawBullet(bullet_t * bullet) {
    if (!bullet->active) return;

    DrawCircleV(bullet->bulletPos, bullet->bulletSize, BLACK);
}

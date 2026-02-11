#include "../../raylib/include/raylib.h"
#include "../../lib/enemies/EnemyProjectiles.h"
#include <math.h>
#include <stdio.h>

void BulletInit(bullet_t * bullet) {
    bullet->bulletSpeed = 590;
    bullet->bulletSize = 20;
    bullet->bulletDmg = 10;
    bullet->bulletPos = (Vector2){ 100, 200};   
    bullet->bulletDir = 30;
}

void BulletUpdate(bullet_t * bullet) {
    float dt = GetFrameTime();
    float angleRad = bullet->bulletDir * DEG2RAD;

    bullet->bulletPos.x += cosf(angleRad) * bullet->bulletSpeed * dt;
    bullet->bulletPos.y += sinf(angleRad) * bullet->bulletSpeed * dt;
}


void BulletDraw(bullet_t * bullet) {
    DrawCircleV(bullet->bulletPos, bullet->bulletSize, BLACK);
}
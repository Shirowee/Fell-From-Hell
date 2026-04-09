#include "../../lib/systems/LifeManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/systems/CollisionSystem.h"
#include "../../lib/player/Player.h"

#define REGEN_TIME 1.0

void PlayerLifeAlteration(Player *player, enemyPool_t *ennemies, bulletPool_t *bullets){
    int dmgToPlayer = 0;
    float dt = GetFrameTime();

    //Perte de vie
    if(!isInvicible(player)){
        CheckPlayerEnemyCollision(player, ennemies, &dmgToPlayer);
        CheckPlayerBulletCollision(player, bullets, &dmgToPlayer);

        if(dmgToPlayer > 0)
            ApplyDamageToPlayer(player, dmgToPlayer);
    }
    else{
        player->stats.invTime -= dt;
    }

    //Gain de vie
    if(canRegen(player)){
        player->stats.regenTimeOut = REGEN_TIME;
        player->stats.hp += player->stats.regen;

        if(player->stats.hp > player->stats.hpMax){
            player->stats.hp = player->stats.hpMax;
        }
    }
    else {
        player->stats.regenTimeOut -= dt;
    }
}

//Applique des dégâts au joueur
void ApplyDamageToPlayer(Player *player, int dmg){
    player->stats.hp -= dmg;
    player->stats.invTime = PLAYER_INVICIBILITY_TIME;
}

void ApplyDamageToEnemy(enemy_t *enemy, int dmg){
    enemy->hp -= dmg;
}

//Dessine barre de vie
void HPDraw(Player *player, int x, int y, int width, int height){
    int gap = 5;
    float ratio = (float)player->stats.hp / (float)player->stats.hpMax;
    Rectangle frame = (Rectangle){x, y, width, height};
    Rectangle healthBar = (Rectangle){x+gap, y+gap, (width-gap*2)*ratio , height-gap*2};

    DrawRectangleRec(frame, GRAY);
    DrawRectangleRec(healthBar, RED);
}

bool isInvicible(Player *player){
    return (player->stats.invTime > 0.0);
}

bool isAlive(Player *player){
    return (player->stats.hp > 0);
}

bool canRegen(Player *player){
    return (player->stats.regenTimeOut <= 0.0);
}
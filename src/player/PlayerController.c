#include "../../lib/player/PlayerController.h"
#include "../../lib/player/PlayerMovement.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/Player.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/systems/EnemyPool.h"
#include "../../lib/systems/LifeManager.h"
#include <stdio.h>

//init le joueur
void PlayerInit(Player *player){
    player->position = (Vector2){ PLAYER_X, PLAYER_Y };
    player->size = (Vector2){ PLAYER_SIZE_X, PLAYER_SIZE_Y };
    player->velocity = (Vector2){ 0, 0 };

    //Initialisation des mouvements du joueur
    player->movConfig.maxSpeed = MAX_SPEED_X;
    player->movConfig.groundAcc = GROUND_ACC;
    player->movConfig.airAcc = AIR_ACC;
    player->movConfig.jumpStrength = JUMP_STRENGTH;
    player->movConfig.gravity = DEFAULT_GRAVITY;
    player->movConfig.fallingGravity = FALLING_GRAVITY;
    player->movConfig.dashTime = 0.0;
    player->movConfig.dashTimeOut = 0.0;

    player->movConfig.nbJumpMax = DEFAULT_JUMPS_MAX;
    player->movConfig.nbJump = DEFAULT_JUMPS_MAX;

    player->movConfig.isOnGround = false;
    player->movConfig.isOnLeftWall = false;
    player->movConfig.isOnRightWall = false;
    player->movConfig.canJump = true;

    //Initialisation de statistiques du joueur
    player->stats.hp = DEFAULT_PLAYER_HP;
    player->stats.hpMax = DEFAULT_PLAYER_HP;
    player->stats.regen = DEFAULT_PLAYER_REGEN;
    player->stats.invTime = 0.0;
    player->stats.regenTimeOut = 1.0;

    //Initialisation de l'arme du joueur
    player->weapon = minigun;

    //Initialisation des buff du joueur
    player->buff = BuffInit();

    PlayerMoveFlagsInit();
    PlayerMoveTimerInit();
}

//maj de la logique du player
void PlayerUpdate(Player *player, Platform platform[], const int nbPlatforms, double* timeSpent, double* startReload){
    PlayerMoveConfigUpdate(player, platform, nbPlatforms);
    PlayerMove(player, platform, nbPlatforms);
    PlayerShoot(player, timeSpent, startReload);
    PlayerLifeAlteration(player, &enemyPool, &bulletPool);
}

//dessine le joueur
void PlayerDraw(Player *player){
    Color color;
    Rectangle body = (Rectangle){player->position.x, player->position.y, player->size.x, player->size.y};

    switch(getPlayerMovementState(player)){
        case IDLE: color = BLUE; break;
        case RUNNING: color = RED; break;
        case JUMPING: color = YELLOW; break;
        case FALLING: color = GREEN; break;
        case WALL_SLIDING: color = PURPLE; break;
        case DASHING: color = PINK; break;
    }

    DrawRectangleRec(body, color);
}

Vector2 getPlayerCenter(Player *player){
    return (Vector2){ player->position.x + player->size.x / 2, player->position.y + player->size.y / 2 };
}
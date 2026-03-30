#include "../../lib/player/PlayerController.h"
#include "../../lib/player/PlayerMovement.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/Player.h"
#include "../../lib/levels/LevelManager.h"

//init le joueur
void PlayerInit(Player *player){
    player->position = (Vector2){ PLAYER_X, PLAYER_Y };
    player->size = (Vector2){ PLAYER_SIZE_X, PLAYER_SIZE_Y };
    player->velocity = (Vector2){ 0, 0 };

    //Initialisation du corps du joueur
    player->body.main = (Rectangle){ PLAYER_X, PLAYER_Y, PLAYER_SIZE_X, PLAYER_SIZE_Y };
    player->body.foot = (Rectangle){ player->body.main.x, player->body.main.y + PLAYER_SIZE_Y, PLAYER_SIZE_X, 1 };

    //Initialisation des mouvements du joueur
    player->movConfig.maxSpeed = MAX_SPEED;
    player->movConfig.groundAcc = GROUND_ACC;
    player->movConfig.airAcc = AIR_ACC;
    player->movConfig.jumpStrength = JUMP_STRENGTH;
    player->movConfig.gravity = DEFAULT_GRAVITY;
    player->movConfig.fallingGravity = FALLING_GRAVITY;

    player->movConfig.nbJumpMax = DEFAULT_JUMPS_MAX;
    player->movConfig.nbJump = DEFAULT_JUMPS_MAX;

    player->movConfig.isOnGround = false;
    player->movConfig.isOnLeftWall = false;
    player->movConfig.isOnRightWall = false;

    player->weapon = minigun;

    PlayerMoveFlagsInit();
    PlayerMoveTimerInit();
}

//maj de la logique du player
void PlayerUpdate(Player *player, Platform platform[], const int nbPlatforms, double* timeSpent, double* startReload){
    PlayerMoveTimerUpdate(player);
    PlayerMoveConfigUpdate(player, platform, nbPlatforms);
    PlayerMove(player, platform, nbPlatforms);
    PlayerMoveFlagsUpdate();
    PlayerShoot(player, timeSpent, startReload);
}

//dessine le joueur
void PlayerDraw(Player *player){
    Color color;

    switch(getPlayerMovementState(player)){
        case IDLE: color = BLUE; break;
        case RUNNING: color = RED; break;
        case JUMPING: color = YELLOW; break;
        case FALLING: color = GREEN; break;
        case WALL_SLIDING: color = PURPLE; break;
        case DASHING: color = PINK; break;
    }

    DrawRectangleRec(player->body.main, color);
}

Vector2 getPlayerCenter(Player *player){
    return (Vector2){ player->position.x + player->size.x / 2, player->position.y + player->size.y / 2 };
}
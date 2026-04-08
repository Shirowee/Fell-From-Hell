#include "../../lib/player/PlayerController.h"
#include "../../lib/player/PlayerMovement.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/Player.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/core/ResolutionManager.h"

//init le joueur
void PlayerInit(Player *player){
    player->position = (Vector2){ PLAYER_X, PLAYER_Y };
    player->size = (Vector2){ RS(PLAYER_SIZE_X), RS(PLAYER_SIZE_Y) };
    player->velocity = (Vector2){ 0, 0 };

    //Initialisation du corps du joueur
    player->body.main = (Rectangle){ RS(PLAYER_X), RS(PLAYER_Y), RS(PLAYER_SIZE_X), RS(PLAYER_SIZE_Y) };
    player->body.foot = (Rectangle){ player->body.main.x, player->body.main.y + RS(PLAYER_SIZE_Y), RS(PLAYER_SIZE_X), 1 };

    //Initialisation des mouvements du joueur
    player->movConfig.maxSpeed = RS(MAX_SPEED);
    player->movConfig.groundAcc = RS(GROUND_ACC);
    player->movConfig.airAcc = RS(AIR_ACC);
    player->movConfig.jumpStrength = RS(JUMP_STRENGTH);
    player->movConfig.gravity = RS(DEFAULT_GRAVITY);
    player->movConfig.fallingGravity = RS(FALLING_GRAVITY);

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


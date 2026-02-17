#include "../../lib/player/PlayerController.h"
#include "../../lib/player/PlayerMovement.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/player/Player.h"
#include "../../lib/levels/LevelManager.h"

//init le joueur
void PlayerInit(void)
{
    //Initialisation du corps du joueur
    player.body.main = (Rectangle){ PLAYER_X, PLAYER_Y, PLAYER_SIZE_X, PLAYER_SIZE_Y };
    player.body.foot = (Rectangle){ player.body.main.x, player.body.main.y + PLAYER_SIZE_Y, PLAYER_SIZE_X, 10 };

    //Initialisation des mouvements du joueur
    player.movement.velocity = (Vector2){ 0, 0 };
    player.movement.maxSpeed = MAX_SPEED;
    player.movement.jumpStrength = JUMP_STRENGTH;
    player.movement.isOnGround = true;
}

//maj de la logique du player
void PlayerUpdate(Platform **platform, const int nbPlatforms)
{
    PlayerMove(platform, nbPlatforms);
}

//dessine le joueur
void PlayerDraw(void)
{
    DrawRectangleRec(player.body.main, BLUE);
}


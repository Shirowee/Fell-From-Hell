#include "../../lib/player/PlayerMovement.h"
#include "../../lib/player/Player.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/core/ResolutionManager.h"
#include "../../lib/core/GameManager.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static Vector2 directionDash = {0,0};


void PlayerMove(Player *player, Platform platform[], const int nbPlatforms) {
    float dt = GetFrameTime(); //Temps entre images
    MovementState state = getPlayerMovementState(player);
    float friction;
    Vector2 oldPosition;

    friction = player->movConfig.isOnGround ? GROUND_FRICTION : AIR_FRICTION;

    //Events de déplacement
    if(state != WALL_SLIDING){
        if (IsKeyDown(KEY_MOVE_RIGHT)) player->velocity.x += (player->movConfig.isOnGround ? player->movConfig.groundAcc : player->movConfig.airAcc) * dt;
        else if (IsKeyDown(KEY_MOVE_LEFT))  player->velocity.x -= (player->movConfig.isOnGround ? player->movConfig.groundAcc : player->movConfig.airAcc) * dt;
        else player->velocity.x *= (fabs(player->velocity.x) > 10 ? friction : 0); // Ralentissement progressif
    }

    if (IsKeyDown(KEY_MOVE_JUMP) && player->movConfig.canJump) PlayerJump(player);
    if (state == FALLING) Gravity(player, player->movConfig.fallingGravity);
    else if (state == JUMPING) Gravity(player, player->movConfig.gravity);
    else if (state == WALL_SLIDING) Gravity(player, WALL_SLIDE_GRAVITY);

    if(state == DASHING) PlayerDash(player);

    //Corretion vitesse
    if(state != DASHING){
        if(player->velocity.x > player->movConfig.maxSpeed) player->velocity.x = player->movConfig.maxSpeed;
        else if(player->velocity.x < -player->movConfig.maxSpeed) player->velocity.x = -player->movConfig.maxSpeed;
    }
    if(player->movConfig.isOnGround) player->velocity.y = 0.0;
    else if(IsKeyReleased(KEY_MOVE_JUMP) && state == JUMPING) player->velocity.y *= 0.5;
    if(state == WALL_SLIDING && player->velocity.y > MAX_WALL_SPEED) player->velocity.y = MAX_WALL_SPEED;
    else if(player->velocity.y > MAX_SPEED_Y) player->velocity.y = MAX_SPEED_Y;



    oldPosition = player->position;

    //Déplacement du joueur
    player->position.x += player->velocity.x * dt;
    player->position.y += player->velocity.y * dt;

    if(state != IDLE)
        PlayerPositionFix(player, oldPosition, platform, nbPlatforms); // Vérification de collision avec les plateformes

    if(IsKeyPressed(KEY_MOVE_JUMP)){
        player->movConfig.canJump = false;
    }
    else if(IsKeyReleased(KEY_MOVE_JUMP)){
        player->movConfig.canJump = true;
    }

}

void PlayerMoveConfigUpdate(Player *player, Platform platform[], const int nbPlatforms){
    float dt = GetFrameTime();
    float length;
    Vector2 mousePos;
    Vector2 playerCenter;


    //Timers
    if(player->movConfig.dashTime > 0.0){
        player->movConfig.dashTime -= dt;
    }
    else if(player->movConfig.dashTime <= 0.0 && player->movConfig.dashTimeOut <= 0.0 && IsKeyPressed(KEY_MOVE_DASH)){
        player->movConfig.dashTime = DASH_TIME_MAX;
        player->stats.invTime = DASH_TIME_MAX;
        player->movConfig.isOnGround = false;

        mousePos = GetMousePosition();
        mousePos.x = camera.target.x + mousePos.x / camera.zoom;
        mousePos.y = camera.target.y + mousePos.y / camera.zoom;

        playerCenter = getPlayerCenter(player);
        directionDash.x = mousePos.x - playerCenter.x;
        directionDash.y = mousePos.y - playerCenter.y;

        length = sqrtf(directionDash.x * directionDash.x + directionDash.y * directionDash.y);

        if (length != 0.0f){
            directionDash.x /= length;
            directionDash.y /= length;
        }
    }

    if(player->movConfig.dashTimeOut > 0.0){
        player->movConfig.dashTimeOut -= dt;
    }
    else if(player->movConfig.dashTimeOut <= 0.0 && player->movConfig.dashTime <= 0.0 && player->movConfig.isDashing){
        player->movConfig.dashTimeOut = 2;
    }

    //Booleens
    if (player->movConfig.isOnGround)
        player->movConfig.isOnGround = isOnGround(player, platform, nbPlatforms);
    if(player->movConfig.isOnLeftWall)
        player->movConfig.isOnLeftWall = isOnWall(player, platform, nbPlatforms, Left);
    if(player->movConfig.isOnRightWall)
        player->movConfig.isOnRightWall = isOnWall(player, platform, nbPlatforms, Right);

    if(player->movConfig.nbJump < player->movConfig.nbJumpMax)
        if(player->movConfig.isOnGround || player->movConfig.isOnLeftWall || player->movConfig.isOnRightWall)
            player->movConfig.nbJump = player->movConfig.nbJumpMax;

    if(player->movConfig.dashTime > 0.0 && (!player->movConfig.isDashing)){
        player->movConfig.isDashing = true;
    }
    if(player->movConfig.dashTimeOut > 0.0)
        player->movConfig.isDashing = false;
}

// Saut
void PlayerJump(Player *player) {

    if(getPlayerMovementState(player) == WALL_SLIDING){
        if (player->movConfig.isOnLeftWall) {
            player->velocity.y = player->movConfig.jumpStrength / 1.5; // Force de saut
            player->velocity.x = -player->movConfig.jumpStrength * 10; // Saut vers la droite
            player->movConfig.isOnLeftWall = false;
            player->movConfig.nbJump--;
        }
        else if (player->movConfig.isOnRightWall) {
            player->velocity.y = player->movConfig.jumpStrength / 1.5; // Force de saut
            player->velocity.x = player->movConfig.jumpStrength * 10; // Saut vers la gauche
            player->movConfig.isOnRightWall = false;
            player->movConfig.nbJump--;
        }
    }
    else if(player->movConfig.isOnGround){
        player->velocity.y = player->movConfig.jumpStrength; // Force de saut
        player->movConfig.isOnGround = false;
        player->movConfig.nbJump--;
    }
    else{
        if(player->movConfig.nbJump){
            player->velocity.y = player->movConfig.jumpStrength / 1.25;
            player->movConfig.nbJump--;
        }
    }
}

// Dash
void PlayerDash(Player *player){
    player->velocity.x = DASH_SPEED * directionDash.x;
    player->velocity.y = DASH_SPEED * directionDash.y;
}

// Gravité
void Gravity(Player *player, const float GravityStrength) {
    player->velocity.y += GravityStrength * GetFrameTime(); // Gravité
}

// Correction de la position du joueur en cas de collision avec les plateformes
void PlayerPositionFix(Player *player, Vector2 oldPosition, Platform platform[], const int nbPlatforms){
    int i;
    int distanceX, distanceY;
    int platformCenterX, platformCenterY;
    int playerCenterX;
    int playerCenterY;

    float prevBottom;
    float currBottom;
    float platformTop;

    bool collision;
    bool wasAbove;
    bool isFalling = player->velocity.y > 0;

    MovementState state = getPlayerMovementState(player);
    Rectangle body = (Rectangle){player->position.x, player->position.y, player->size.x, player->size.y};

    for(i = 0; i < nbPlatforms; i++) {
        //Ne vérifie que pour les plateformes les plus proches
        if(platform[i].rect.x + platform[i].rect.width < player->position.x - PLAYER_MAX_DIST_DETECT || 
            platform[i].rect.x > player->position.x + PLAYER_MAX_DIST_DETECT) continue;
        if(platform[i].rect.y + platform[i].rect.height < player->position.y - PLAYER_MAX_DIST_DETECT ||
            platform[i].rect.y > player->position.y + PLAYER_MAX_DIST_DETECT) continue;


        collision = false;
        // Calcul du centre de la plateforme
        platformCenterX = platform[i].rect.x + platform[i].rect.width / 2;
        platformCenterY = platform[i].rect.y + platform[i].rect.height / 2;

        if(platform[i].solid) {
            if(CheckCollisionRecs(body, platform[i].rect)){
                collision = true;
                // Calcul du centre de la rectangle main
                playerCenterX = player->position.x + player->size.x / 2;
                playerCenterY = player->position.y + player->size.y / 2;

                // Calcul de la distance entre le joueur et la plateforme
                distanceX = (player->size.x / 2 + platform[i].rect.width / 2) - abs(playerCenterX - platformCenterX);
                distanceY = (player->size.y / 2 + platform[i].rect.height / 2) - abs(playerCenterY - platformCenterY);

                if(distanceX < distanceY) { // Collision sur l'axe x
                    if (playerCenterX < platformCenterX) {
                        player->position.x = platform[i].rect.x - player->size.x; // Collision à droite
                        if(state == JUMPING || state == FALLING){
                            player->movConfig.isOnLeftWall = false;
                            player->movConfig.isOnRightWall = true;
                            player->velocity.y = 0;
                        }
                    } else {
                        player->position.x = platform[i].rect.x + platform[i].rect.width; // Collision à gauche
                        if(state == JUMPING || state == FALLING){
                            player->movConfig.isOnLeftWall = true;
                            player->movConfig.isOnRightWall = false;
                            player->velocity.y = 0;
                        }
                    }
                    player->velocity.x = 0; // Arrêter le mouvement horizontal
                    if(state == DASHING)
                        player->movConfig.isDashing = false;
                }
                else { // Collision sur l'axe y
                    if (playerCenterY < platformCenterY) {
                        player->position.y = platform[i].rect.y - player->size.y; // Collision en bas
                        if (state == FALLING) {
                            player->movConfig.isOnGround = true;
                            player->velocity.y = 0; // Arrêter le mouvement vertical
                        }
                        if (state == WALL_SLIDING) {
                            player->movConfig.isOnGround = true;
                            player->movConfig.isOnLeftWall = false;
                            player->movConfig.isOnRightWall = false;
                            player->velocity.y = 0;
                        }
                    } 
                    else {
                        player->position.y = platform[i].rect.y + platform[i].rect.height; // Collision en haut
                        if (state == JUMPING) {
                            player->velocity.y = 0; // Arrêter le mouvement vertical
                        }
                        if(state == DASHING)
                            player->movConfig.isDashing = false;
                    }
                }
            }
        }
        else {
            prevBottom = oldPosition.y + player->size.y;
            currBottom = player->position.y + player->size.y;
            platformTop = platform[i].rect.y;

            wasAbove = prevBottom <= platformTop;

            if(wasAbove && isFalling && currBottom >= platformTop && CheckCollisionRecs(body, platform[i].rect)){
                player->position.y = platform[i].rect.y - player->size.y; // Collision en bas
                player->velocity.y = 0; // Arrêter le mouvement vertical
                player->movConfig.isOnGround = true;
                collision = true;
                if (state == WALL_SLIDING) {
                    player->movConfig.isOnLeftWall = false;
                    player->movConfig.isOnRightWall = false;
                    player->velocity.y = 0;
                }
            }
        }

        if(collision){
            // Mettre à jour le corps du joueur après correction de position
            body.x = player->position.x;
            body.y = player->position.y;
        }
    }
}

// Vérifie si le joueur est au sol en vérifiant la collision entre le pied du joueur et les plateformes
bool isOnGround(Player *player, Platform platform[], const int nbPlatforms) {
    int i;
    Rectangle foot = (Rectangle){player->position.x, player->position.y + player->size.y, player->size.x, 1};
    bool grounded = false;

    for(i = 0; i < nbPlatforms; i++) {
        //Ne vérifie que pour les plateformes les plus proches
        if(platform[i].rect.x + platform[i].rect.width < player->position.x - PLAYER_MAX_DIST_DETECT || 
            platform[i].rect.x > player->position.x + PLAYER_MAX_DIST_DETECT) continue;
        if(platform[i].rect.y + platform[i].rect.height < player->position.y - PLAYER_MAX_DIST_DETECT ||
            platform[i].rect.y > player->position.y + PLAYER_MAX_DIST_DETECT) continue;

        if (CheckCollisionRecs(foot, platform[i].rect)) {
            if (getPlayerMovementState(player) != JUMPING && foot.y <= platform[i].rect.y) {
                grounded = true; // Le pied du joueur touche une plateforme
            }
        }
    }
    return grounded;
}

// Vérifie si le joueur est sur un mur
bool isOnWall(Player *player, Platform platform[], const int nbPlatforms, Direction dir) {
    int i;
    Rectangle checker;

    if(!player->movConfig.isOnGround){
        if(dir == Left){
            checker = (Rectangle){player->position.x - 5, player->position.y, 5, player->size.y};
        }
        else if(dir == Right){
            checker = (Rectangle){player->position.x + player->size.x, player->position.y, 5, player->size.y};
        }
        else{
            return false;
        }

        for(i = 0; i < nbPlatforms; i++) {
            //Ne vérifie que pour les plateformes les plus proches
            if(platform[i].rect.x + platform[i].rect.width < player->position.x - PLAYER_MAX_DIST_DETECT || 
                platform[i].rect.x > player->position.x + PLAYER_MAX_DIST_DETECT) continue;
            if(platform[i].rect.y + platform[i].rect.height < player->position.y - PLAYER_MAX_DIST_DETECT ||
                platform[i].rect.y > player->position.y + PLAYER_MAX_DIST_DETECT) continue;

            if (platform[i].solid && CheckCollisionRecs(checker, platform[i].rect)) {
                return true; // Le joueur touche un mur
            }
        }
    }
    return false;
}

MovementState getPlayerMovementState(Player *player) {
    if(player->movConfig.isDashing)
        return DASHING;

    if(player->movConfig.isOnGround) {
        if(player->velocity.x != 0) {
            return RUNNING;
        }
        return IDLE;
    } else {
        if(player->movConfig.isOnLeftWall || player->movConfig.isOnRightWall) {
            return WALL_SLIDING;
        }
        if(player->velocity.y < 0) {
            return JUMPING;
        }
        return FALLING;
    }
}

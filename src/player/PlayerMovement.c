#include "../../lib/player/PlayerMovement.h"
#include "../../lib/player/Player.h"
#include "../../lib/levels/LevelManager.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static MovFlags flags;
MovTimer timer;

void PlayerMove(Player *player, Platform platform[], const int nbPlatforms) {
    float dt = GetFrameTime(); //Temps entre images

    if(player->movConfig.isOnGround) player->movConfig.isOnGround = isOnGround(player, platform, nbPlatforms); // Vérifie si le joueur est au sol

    //Events de déplacement
    if(getPlayerMovementState(player) != WALL_SLIDING){
        if (IsKeyDown(KEY_RIGHT)) player->velocity.x += (player->movConfig.isOnGround ? player->movConfig.groundAcc : player->movConfig.airAcc) * dt;
        else if (IsKeyDown(KEY_LEFT))  player->velocity.x -= (player->movConfig.isOnGround ? player->movConfig.groundAcc : player->movConfig.airAcc) * dt;
        else player->velocity.x *= (player->movConfig.isOnGround ? (fabs(player->velocity.x) > 10 ? powf(GROUND_FRICTION, dt) : 0) : powf(AIR_FRICTION, dt)); // Ralentissement progressif
    }

    if (IsKeyDown(KEY_SPACE) && timer.jumpTimeOut <= 0.0) PlayerJump(player);
    if (getPlayerMovementState(player) == FALLING) Gravity(player, player->movConfig.fallingGravity);
    else if (getPlayerMovementState(player) == JUMPING) Gravity(player, player->movConfig.gravity);
    else if (getPlayerMovementState(player) == WALL_SLIDING) Gravity(player, WALL_SLIDE_GRAVITY);

    if(getPlayerMovementState(player) == DASHING) PlayerDash(player);

    //Corretion vitesse
    if(getPlayerMovementState(player) != DASHING){
        if(player->velocity.x > player->movConfig.maxSpeed) player->velocity.x = player->movConfig.maxSpeed;
        else if(player->velocity.x < -player->movConfig.maxSpeed) player->velocity.x = -player->movConfig.maxSpeed;
    }

    if(player->movConfig.isOnGround) player->velocity.y = 0.0;
    else if(IsKeyReleased(KEY_SPACE) || (timer.jumpTime <= 0.0 && getPlayerMovementState(player) == JUMPING)) player->velocity.y *= 0.5;
    if(getPlayerMovementState(player) == WALL_SLIDING && player->velocity.y > MAX_WALL_SPEED) player->velocity.y = MAX_WALL_SPEED;

    //Déplacement du joueur
    if(player->velocity.x != 0){
        player->position.x += player->velocity.x * dt;
    }
    if(player->velocity.y != 0){
        player->position.y += player->velocity.y * dt;
    }

    // Mettre à jour le corps du joueur après déplacement
    player->body.main.x = player->position.x;
    player->body.main.y = player->position.y;
    player->body.foot.x = player->position.x;
    player->body.foot.y = player->position.y + player->size.y;

    PlayerPositionFix(player, platform, nbPlatforms); // Vérification de collision avec les plateformes
}

void PlayerMoveConfigUpdate(Player *player, Platform platform[], const int nbPlatforms){
    player->movConfig.isOnGround = isOnGround(player, platform, nbPlatforms);
    if(player->movConfig.isOnLeftWall)
        player->movConfig.isOnLeftWall = isOnWall(player, platform, nbPlatforms, Left);
    if(player->movConfig.isOnRightWall)
        player->movConfig.isOnRightWall = isOnWall(player, platform, nbPlatforms, Right);

    if(player->movConfig.nbJump < player->movConfig.nbJumpMax)
        if(player->movConfig.isOnGround || player->movConfig.isOnLeftWall || player->movConfig.isOnRightWall)
            player->movConfig.nbJump = player->movConfig.nbJumpMax;

    if(timer.dashTimeOut <= 0.0 && IsKeyDown(KEY_C) && (!player->movConfig.isDashing)){
        player->movConfig.isDashing = true;
    }
    if(timer.dashTimeOut > 0.0)
        player->movConfig.isDashing = false;
}

void PlayerMoveFlagsInit(){
    flags.jumpMovePressed = false;
    flags.leftMovePressed = false;
    flags.rightMovePressed = false;
}

void PlayerMoveTimerInit(){
    timer.jumpTime = 0.0;
    timer.jumpTimeOut = 0.0;
    timer.dashTime = 0.0;
    timer.dashTimeOut = 0.0;
}

void PlayerMoveFlagsUpdate(){
    if(IsKeyPressed(KEY_SPACE)){
        flags.jumpMovePressed = true;
    }
    else if(IsKeyReleased(KEY_SPACE)){
        flags.jumpMovePressed = false;
    }

    if(IsKeyPressed(KEY_LEFT)){
        flags.leftMovePressed = true;
    }
    else if(IsKeyReleased(KEY_LEFT)){
        flags.leftMovePressed = false;
    }

    if(IsKeyPressed(KEY_RIGHT)){
        flags.rightMovePressed = true;
    }
    else if(IsKeyReleased(KEY_RIGHT)){
        flags.rightMovePressed = false;
    }
}

void PlayerMoveTimerUpdate(Player *player){
    float dt = GetFrameTime();

    if(timer.jumpTime > 0.0){
        timer.jumpTime -= dt;
    }
    else if(timer.jumpTime <= 0.0 && IsKeyPressed(KEY_SPACE)){
        timer.jumpTime = 0.5;
    }

    if(timer.jumpTimeOut > 0.0 && (player->movConfig.isOnGround || getPlayerMovementState(player) == WALL_SLIDING)){
        timer.jumpTimeOut -= dt;
    }
    else if(timer.jumpTimeOut <= 0.0 && player->movConfig.nbJump == 0 && player->movConfig.isOnGround){
        timer.jumpTimeOut = 0.1;
    }

    if(timer.dashTime > 0.0){
        timer.dashTime -= dt;
    }
    else if(timer.dashTime <= 0.0 && timer.dashTimeOut <= 0.0 && IsKeyDown(KEY_C)){
        timer.dashTime = 0.2;
    }

    if(timer.dashTimeOut > 0.0){
        timer.dashTimeOut -= dt;
    }
    else if(timer.dashTimeOut <= 0.0 && timer.dashTime <= 0.0 && player->movConfig.isDashing){
        timer.dashTimeOut = 2;
    }
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
        if(player->movConfig.nbJump && (!flags.jumpMovePressed)){
            player->velocity.y = player->movConfig.jumpStrength / 1.5;
            player->movConfig.nbJump--;
        }
    }
}

// Dash
void PlayerDash(Player *player){
    if(player->velocity.x > 0.0){
        player->velocity.x = DASH_SPEED;
    }
    else if(player->velocity.x < 0.0){
        player->velocity.x = -DASH_SPEED;
    }
    else{
        timer.dashTime = 0.0;
        return;
    }
    player->velocity.y = 0;
    player->velocity.y = 0;

}

// Gravité
void Gravity(Player *player, const float GravityStrength) {
    player->velocity.y += GravityStrength * GetFrameTime(); // Gravité
}

// Correction de la position du joueur en cas de collision avec les plateformes
void PlayerPositionFix(Player *player, Platform platform[], const int nbPlatforms) {
    int i;
    int distanceX, distanceY;
    int platformCenterX, platformCenterY;
    int playerCenterX;
    int playerCenterY;
    bool collision;
    MovementState state = getPlayerMovementState(player);

    for(i = 0; i < nbPlatforms; i++) {
        collision = false;
        // Calcul du centre de la plateforme
        platformCenterX = platform[i].rect.x + platform[i].rect.width / 2;
        platformCenterY = platform[i].rect.y + platform[i].rect.height / 2;

        if(platform[i].solid) {
            if(CheckCollisionRecs(player->body.main, platform[i].rect)){
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
                    }
                }
            }
        }
        else {
            if(state != JUMPING && CheckCollisionRecs(player->body.foot, platform[i].rect)){
                player->position.y = platform[i].rect.y - player->size.y; // Collision en bas
                player->velocity.y = 0; // Arrêter le mouvement vertical
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
            player->body.main.x = player->position.x;
            player->body.main.y = player->position.y;
            player->body.foot.x = player->position.x;
            player->body.foot.y = player->position.y + player->size.y;
        }
    }
}

// Vérifie si le joueur est au sol en vérifiant la collision entre le pied du joueur et les plateformes
bool isOnGround(Player *player, Platform platform[], const int nbPlatforms) {
    int i;

    for(i = 0; i < nbPlatforms; i++) {
        if (CheckCollisionRecs(player->body.foot, platform[i].rect)) {
            if (getPlayerMovementState(player) != JUMPING && player->body.foot.y <= platform[i].rect.y) {
                return true; // Le pied du joueur touche une plateforme
            }
            return false;
        }
    }
    return false;
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

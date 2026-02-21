#include "../../lib/player/PlayerMovement.h"
#include "../../lib/player/Player.h"
#include "../../lib/levels/LevelManager.h"
#include <stdio.h>
#include <math.h>

//Déplacements latéraux
void PlayerMove(Player *player, Platform **platform, const int nbPlatforms) {
    float dt = GetFrameTime(); //Temps entre images

    player->movConfig.isOnGround = isOnGround(player, platform, nbPlatforms); // Vérifie si le joueur est au sol

    //Events de déplacement
    if (IsKeyDown(KEY_RIGHT)) player->velocity.x += player->movConfig.groundAcc;
    else if (IsKeyDown(KEY_LEFT))  player->velocity.x -= player->movConfig.groundAcc;
    else player->velocity.x *= ( fabs(player->velocity.x) > 10 ? 0.5 : 0 ); // Ralentissement progressif

    if (IsKeyDown(KEY_SPACE)) PlayerJump(player);
    if (getPlayerMovementState(player) == FALLING) Gravity(player, player->movConfig.gravity * 1.5);
    else if (getPlayerMovementState(player) == JUMPING) Gravity(player, player->movConfig.gravity);

    //Corretion vitesse
    if(player->velocity.x > player->movConfig.maxSpeed) player->velocity.x = player->movConfig.maxSpeed;
    else if(player->velocity.x < -player->movConfig.maxSpeed) player->velocity.x = -player->movConfig.maxSpeed;

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

// Saut
void PlayerJump(Player *player) {
    if (player->movConfig.isOnGround) {
        player->velocity.y = player->movConfig.jumpStrength; // Force de saut
        player->movConfig.isOnGround = false;
    }
    else if (player->movConfig.isOnLeftWall) {
        player->velocity.y = player->movConfig.jumpStrength / 2; // Force de saut
        player->velocity.x = -player->movConfig.jumpStrength / 2 ; // Saut vers la droite
        player->movConfig.isOnLeftWall = false;
    }
    else if (player->movConfig.isOnRightWall) {
        player->velocity.y = player->movConfig.jumpStrength / 2; // Force de saut
        player->velocity.x = player->movConfig.jumpStrength / 2 ; // Saut vers la gauche
        player->movConfig.isOnRightWall = false;
    }
}

// Gravité
void Gravity(Player *player, const float GravityStrength) {
    player->velocity.y += GravityStrength * GetFrameTime(); // Gravité
}

// Correction de la position du joueur en cas de collision avec les plateformes
void PlayerPositionFix(Player *player, Platform **platform, const int nbPlatforms) {
    int i;
    int distanceX, distanceY;
    int platformCenterX, platformCenterY;
    int playerCenterX = player->position.x + player->size.x / 2;
    int playerCenterY = player->position.y + player->size.y / 2;

    for(i = 0; i < nbPlatforms; i++) {
        if (CheckCollisionRecs(player->body.main, platform[i]->rect)) {
            //Calcul du centre de la plateforme
            platformCenterX = platform[i]->rect.x + platform[i]->rect.width / 2;
            platformCenterY = platform[i]->rect.y + platform[i]->rect.height / 2;

            // Calcul de la distance entre le joueur et la plateforme
            distanceX = (player->size.x / 2 + platform[i]->rect.width / 2) - abs(playerCenterX - platformCenterX);
            distanceY = (player->size.y / 2 + platform[i]->rect.height / 2) - abs(playerCenterY - platformCenterY);

            if(distanceX < distanceY) { // Collision sur l'axe x
                if (playerCenterX < platformCenterX) {
                    player->position.x = platform[i]->rect.x - player->size.x; // Collision à droite
                } else {
                    player->position.x = platform[i]->rect.x + platform[i]->rect.width; // Collision à gauche
                }
                player->velocity.x = 0; // Arrêter le mouvement horizontal
            } else { // Collision sur l'axe y
                if (playerCenterY < platformCenterY) {
                    player->position.y = platform[i]->rect.y - player->size.y; // Collision en bas
                    if (player->velocity.y >= 0) {
                        player->velocity.y = 0; // Arrêter le mouvement vertical
                    }
                } else {
                    player->position.y = platform[i]->rect.y + platform[i]->rect.height; // Collision en haut
                    if (player->velocity.y <= 0) {
                        player->velocity.y = 0; // Arrêter le mouvement vertical
                    }
                }
            }
        }
    }

    // Mettre à jour le corps du joueur après correction de position
    player->body.main.x = player->position.x;
    player->body.main.y = player->position.y;
    player->body.foot.x = player->position.x;
    player->body.foot.y = player->position.y + player->size.y;
}

// Vérifie si le joueur est au sol en vérifiant la collision entre le pied du joueur et les plateformes
bool isOnGround(Player *player, Platform **platform, const int nbPlatforms) {
    int i;

    for(i = 0; i < nbPlatforms; i++) {
        if (CheckCollisionRecs(player->body.foot, platform[i]->rect)) {
            if (player->velocity.y >= 0) {
                return true; // Le pied du joueur touche une plateforme
            }
            return false; // Le pied du joueur est en collision mais le joueur monte, donc pas au sol
        }
    }
    return false;
}

MovementState getPlayerMovementState(Player *player) {
    if(player->movConfig.isOnLeftWall || player->movConfig.isOnRightWall) {
        return WALL_SLIDING;
    }
    
    if(player->movConfig.isOnGround) {
        if(player->velocity.x != 0) {
            return RUNNING;
        }
    } else {
        if(player->velocity.y < 0) {
            return JUMPING;
        }
        return FALLING;
    }

    return IDLE;
}
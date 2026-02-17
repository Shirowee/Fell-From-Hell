#include "../../lib/player/PlayerMovement.h"
#include "../../lib/player/Player.h"
#include "../../lib/levels/LevelManager.h"
#include <stdio.h>
#include <math.h>

//Déplacements latéraux
void PlayerMove(Platform **platform, const int nbPlatforms)
{
    float dt = GetFrameTime(); //Temps entre images
    PlayerMovement *pm = &player.movement; //Raccourci pour accéder aux mouvements du joueur

    pm->isOnGround = isOnGround(platform, nbPlatforms); // Vérifie si le joueur est au sol

    //Events de déplacement
    if (IsKeyDown(KEY_RIGHT)) pm->velocity.x = pm->maxSpeed;
    else if (IsKeyDown(KEY_LEFT))  pm->velocity.x = -pm->maxSpeed;

    if (IsKeyDown(KEY_SPACE)) PlayerJump();
    if (!pm->isOnGround) Gravity();

    //Déplacement du joueur
    if(pm->velocity.x != 0){
        player.body.main.x += pm->velocity.x * dt;
        pm->velocity.x *= ( fabs(pm->velocity.x) > 10 ? 0.8f : 0 ); // Ralentissement progressif
    }
    if(pm->velocity.y != 0){
        player.body.main.y += pm->velocity.y * dt;
    }

    // Mettre à jour foot après déplacement
    player.body.foot.x = player.body.main.x;
    player.body.foot.y = player.body.main.y + player.body.main.height;

    PlayerBodyFix(platform, nbPlatforms); // Vérification de collision avec les plateformes
}

// Saut
void PlayerJump(void){
    if (player.movement.isOnGround) {
        player.movement.velocity.y = player.movement.jumpStrength; // Force de saut
        player.movement.isOnGround = false;
    }
}

// Gravité
void Gravity(void) {
    player.movement.velocity.y += GRAVITY * GetFrameTime(); // Gravité
}

// Correction de la position du joueur en cas de collision avec les plateformes
void PlayerBodyFix(Platform **platform, const int nbPlatforms) {
    int i;
    int distanceX, distanceY;
    int platformCenterX, platformCenterY;
    int playerCenterX = player.body.main.x + player.body.main.width / 2;
    int playerCenterY = player.body.main.y + player.body.main.height / 2;

    // Vérifie les collisions sur l'axe y
    for(i = 0; i < nbPlatforms; i++) {
        
    }

    // Vérifie les collisions sur l'axe x
    for(i = 0; i < nbPlatforms; i++) {
        if (CheckCollisionRecs(player.body.main, platform[i]->rect)) {
            //Calcul du centre de la plateforme
            platformCenterX = platform[i]->rect.x + platform[i]->rect.width / 2;
            platformCenterY = platform[i]->rect.y + platform[i]->rect.height / 2;

            // Calcul de la distance entre le joueur et la plateforme
            distanceX = (player.body.main.width / 2 + platform[i]->rect.width / 2) - abs(playerCenterX - platformCenterX);
            distanceY = (player.body.main.height / 2 + platform[i]->rect.height / 2) - abs(playerCenterY - platformCenterY);

            if(distanceX < distanceY) { // Collision sur l'axe x
                if (playerCenterX < platformCenterX) {
                    player.body.main.x = platform[i]->rect.x - player.body.main.width; // Collision à droite
                } else {
                    player.body.main.x = platform[i]->rect.x + platform[i]->rect.width; // Collision à gauche
                }
                player.movement.velocity.x = 0; // Arrêter le mouvement horizontal
            } else { // Collision sur l'axe y
                if (playerCenterY < platformCenterY) {
                    player.body.main.y = platform[i]->rect.y - player.body.main.height; // Collision en bas
                    if (player.movement.velocity.y >= 0.0f) {
                        player.movement.velocity.y = 0; // Arrêter le mouvement vertical
                    }
                } else {
                    player.body.main.y = platform[i]->rect.y + platform[i]->rect.height; // Collision en haut
                    if (player.movement.velocity.y <= 0.0f) {
                        player.movement.velocity.y = 0; // Arrêter le mouvement vertical
                    }
                }
            }
        }
    }

    // Mettre à jour foot après correction de position
    player.body.foot.x = player.body.main.x;
    player.body.foot.y = player.body.main.y + player.body.main.height;
}

// Vérifie si le joueur est au sol en vérifiant la collision entre le pied du joueur et les plateformes
bool isOnGround(Platform **platform, const int nbPlatforms) {
    int i;

    for(i = 0; i < nbPlatforms; i++) {
        if (CheckCollisionRecs(player.body.foot, platform[i]->rect)) {
            if (player.movement.velocity.y >= 0.0f) {
                return true; // Le pied du joueur touche une plateforme
            }
            return false; // Le pied du joueur est en collision mais le joueur monte, donc pas au sol
        }
    }
    return false;
}
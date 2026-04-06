/**
 * @file EnemyMovement.h
 * @brief Gestion du mouvement des ennemis
 *
 * Contient les fonctions responsables du déplacement
 * des ennemis dans le jeu.
 *
 * Implémente différentes logiques de mouvement selon le type
 * ou l’état de l’ennemi, par exemple :
 * - déplacement aléatoire
 * - poursuite du joueur
 * - déplacement directionnel simple
 * - comportement basé sur une machine à états
 *
 *
 * @author A. Pocholle
 */
 
#include "../../lib/enemies/EnemyMovement.h"
#include "../../lib/enemies/EnemyController.h"
#include "../../raylib/include/raylib.h"
#include <math.h>

//Déplacements
void EnemyMove(enemy_t * enemy)
{
    float dt = GetFrameTime();

    float angleRad = enemy->dir * DEG2RAD;

    enemy->pos.x += cosf(angleRad) * enemy->speed * dt;
    enemy->pos.y += sinf(angleRad) * enemy->speed * dt;
}

void EnemyMoveTowardsPlayer(enemy_t *enemy, Vector2 player)
{
    float dt = GetFrameTime();

    // Soustracion  
    Vector2 direction;
    direction.x = player.x - enemy->pos.x;
    direction.y = player.y - enemy->pos.y;

    // longueur vect
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.0f)
    {
        // Normalisation
        direction.x /= length;
        direction.y /= length;

        enemy->pos.x += direction.x * enemy->speed * dt;
        enemy->pos.y += direction.y * enemy->speed * dt;
    }
}
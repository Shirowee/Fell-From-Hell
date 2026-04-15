/**
 * @file Parallax.h
 * @brief Système de parallax scrolling (fonds multi-couches)
 * @author A. Pocholle
 */

#ifndef PARALLAX_H
#define PARALLAX_H

#include "../../raylib/include/raylib.h"
#include "../../lib/player/Player.h"

#define PARALLAX_MAX_LAYERS 8

/**
 * @brief Représente une couche de parallax
 */
typedef struct ParallaxLayer_s
{
    Texture2D texture;   /**< Texture de la couche */
    float speed;         /**< Facteur de vitesse (0 = fixe, 1 = suit la caméra) */
    Vector2 offset;      /**< Offset manuel (optionnel) */
} ParallaxLayer;

/**
 * @brief Système de parallax complet
 */
typedef struct ParallaxSystem_s
{
    ParallaxLayer layers[PARALLAX_MAX_LAYERS]; /**< Tableau de couches */
    int layerCount;                             /**< Nombre de couches actives */
} ParallaxSystem;

/*==================== INIT ====================*/

/**
 * @brief Initialise le système de parallax
 */
void ParallaxInit(ParallaxSystem *ps);

/**
 * @brief Ajoute une couche au système
 * @param ps système
 * @param texture texture de la couche
 * @param speed facteur de vitesse (0..1)
 */
void ParallaxAddLayer(ParallaxSystem *ps, Texture2D texture, float speed);

/*==================== UPDATE / DRAW ====================*/

/**
 * @brief Dessine toutes les couches de parallax
 * @param ps système
 * @param camera caméra du jeu
 * @param player joueur
 */
void ParallaxDraw(ParallaxSystem *ps, Camera2D camera, Player *player);

#endif
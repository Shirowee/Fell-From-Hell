/**
 * \file Platform.h
 * \author Thomas
 * \brief Définition des structures de base pour des positions et des rectangles
 * * Ce fichier contient les structures de Pos (qui contient des coordonnées x et y),
 * ainsi que celle Rect (utilisé pour les zones et autres) et la structure Platform qui contient 
 * les informations sur une platformes
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../raylib/include/raylib.h"

/**
 * @struct Pos
 * @brief Structure simple qui contient uniquement deux coordonnées x et y
 */
typedef struct {
    int x;      /**< Position horizontale (x) */
    int y;      /**< Position verticale (y) */
} Pos;


/**
 * @struct Rect
 * @brief Structure contenant les informations d'un rectangle
 */
typedef struct {
    float x;    /**< Position x du coin haut gauche */
    float y;    /**< Position y du coin haut gauche */
    float w;    /**< Largeur du rectangle */
    float h;    /**< Hauteur du rectangle */
} Rect;


/**
 * @struct Platform
 * @brief Représente une plateforme dans le jeu
 */
typedef struct {
    char type[32];              /**< Nom du type de plateforme*/
    int solid;                  /**< Flag pour la collision de la platform : 1 si dur, 0 si traversable */
    float x, y, width, high;    /**< Informations sur la position et la taille de la platforme */
    Rectangle rect; 
    Color color;                /**< Couleur de la plateforme */

} Platform;

#endif

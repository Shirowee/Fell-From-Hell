/**
 * \file ResolutionManager.h
 * \author Thomas
 * \brief Sert a gérer la mise à l'échelle dynamiquement
 * Ce fichier sert à adapter les coordonnées du JSON à la résolution réelles de l'écran 
 * afin que le rendu soit identique peut importe la taille de celui-ci
 */

#ifndef RESOLUTION_MANAGER_H
#define RESOLUTION_MANAGER_H

#include <math.h>


/**
 * @struct ResolutionConfig
 * @brief Stocke les paramètres globale pour la mise a l'échelle
 */
typedef struct {
    float   scale;    /**< Ratio de multiplication (Écran Réel / taille Référence) */
    float   screenW;     /**< Largeur de l'écran*/
    float   screenH;     /**< Hauteur de l'écran*/
} ResolutionConfig;


extern ResolutionConfig resolution;

/**
 * @brief Initialise la mise à l'échelle
 * * Calcule le ratio en comparant la largeur de l'écran actuelle avec la largeur de référence en paramètre
 * * @param mapRefWidth Largeur cible de référence de la map
 * @param screenWidth Largeur de l'écran
 * @param screenHeight Hauteur de l'écran
 */
void ResolutionInit(int mapRefWidth, int screenWidth, int screenHeight);

/**
 * @brief Convertit la valeur en paramètre avec le ratio scale
 * * @param value Valeur en pixels "fixe" du JSON
 * @return float Valeur mise à l'échelle pour l'affichage
 */
float RS(float value);

#endif
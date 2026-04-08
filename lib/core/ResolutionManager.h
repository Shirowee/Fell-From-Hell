/* jsp c koi ce bloc

/**
 * \file ResolutionManager.h
 * \author Thomas
 * \brief Sert a gérer la mise à l'échelle dynamiquement
 * Ce fichier sert à adapter les coordonnées du JSON à la résolution réelles de l'écran 
 * afin que le rendu soit identique peut importe la taille de celui-ci

ResolutionManager.h
2 Ko
#include "../../lib/core/ResolutionManager.h"
#include "../../raylib/include/raylib.h"

ResolutionConfig resolution;

void ResolutionInit(int mapRefWidth, int mapRefHeight) {

ResolutionManager.c
1 Ko
﻿
Thokill
thokill
 
*/
 
 
 
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
    float scale;    /**< Ratio de multiplication (Écran Réel / taille Référence) */
    int   refW;     /**< Largeur de référence*/
    int   refH;     /**< Hauteur de référence*/
} ResolutionConfig;


extern ResolutionConfig resolution;

/**
 * @brief Initialise la mise à l'échelle
 * * Calcule le ratio en comparant la largeur de l'écran actuelle avec la largeur de référence en paramètre
 * * @param mapRefWidth Largeur cible de référence
 * @param mapRefHeight Hauteur cible de référence
 */
void ResolutionInit(int mapRefWidth, int mapRefHeight);

/**
 * @brief Convertit la valeur en paramètre avec le ratio scale
 * * @param value Valeur en pixels "fixe" du JSON
 * @return float Valeur mise à l'échelle pour l'affichage
 */
float RS(float value);

#endif
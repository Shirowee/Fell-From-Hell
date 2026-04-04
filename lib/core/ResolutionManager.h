#ifndef RESOLUTION_MANAGER_H
#define RESOLUTION_MANAGER_H

#include <math.h>

typedef struct {
    float scale;    // Scale qui servira a tout rendre uniforme
    int   refW;     // Largeur de référence de la map
    int   refH;     // Hauteur de référence de la map
} ResolutionConfig;

extern ResolutionConfig resolution;

void ResolutionInit(int mapRefWidth, int mapRefHeight);
float RS(float value);

#endif
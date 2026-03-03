#include "../raylib/include/raylib.h"

typedef enum{
    AUCUN,
    FEU,
    GEL,
    ELECTRIQUE,
    MALEDICTION,
    BENEDICTION
}effet_t;

typedef struct{
    float degats;
    float tps;                  //tir par seconde
    int chargeur;               //nombre de munition
    float temps_rechargement;   //en secondes
    effet_t effet;              //effet de l'arme
    int dispersion;             //rayon de dispersion de l'arme
    int porte;                  //porté de l'arme
}arme_t;
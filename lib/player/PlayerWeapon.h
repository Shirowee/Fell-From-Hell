#ifndef PLAYER_WEAPON_H
#define PLAYER_WEAPON_H

#include "../../raylib/include/raylib.h"
//#include "../systems/Projectiles.h"
#include "../systems/BulletPool.h"


typedef enum{
    AUCUN,
    TOUS,
    FEU,
    GEL,
    ELECTRIQUE,
    MALEDICTION,
    BENEDICTION
}effect_t;

typedef struct{
    float degats;
    float tps;                  //tir par seconde
    int chargeur;               //nombre de munition
    float temps_rechargement;   //en secondes
    effect_t effet;              //effet de l'arme
    int dispersion;             //rayon de dispersion de l'arme
    int porte;                  //porté de l'arme entre 0 et 100
}weapon_t;


//definition des armes

weapon_t minigun ={12.5, 10, 75, 3, AUCUN, 20, 100};
//description : tir vite avec dispersion, grand chargeur
weapon_t lance_flammes ={10, 20, 300, 3, FEU, 30, 20};
//description : peu de dégâts mais brûle
weapon_t lance_missile_tete_chercheuse ={125, 2, 10, 6, AUCUN, 0, 100};
//description : lance un missile qui se dirige vers l’ennemi le plus proche, cadence de tir élevée, temps de rechargement long
weapon_t fusil_a_pompe ={12.5, 0.5, 6, 5, AUCUN, 50, 20};
//description : tir 9 balles en forme de cone
weapon_t pistolet_laser ={50, 0.8, 10, 3, AUCUN, 0, 100};
//description : tir un rayon laser qui reste pendant 1sec
weapon_t fusil_rafales ={35, 2, 11, 3, AUCUN, 10, 100};
//description : tir trois balles d’affilées
weapon_t lance_glace ={10, 20, 300, 3, GEL, 30, 20};
//description : lance flamme mais type gel
weapon_t lance_roquette ={150, 0.8, 8, 4, FEU, 0, 50};
//description : tir un missile en ligne droite qui explose au bout de x sec
weapon_t epee_longue ={75, 1.5, -1, -1, AUCUN, 160, 10};
//description : attaque en face avec un grand angle (style reinhardt)
weapon_t sniper ={150, 0.5, 6, 3, AUCUN, 0, 100};
//description : cadence de tir lente et petit chargeur mais grosse balle et bcp de dégâts
weapon_t arbalete ={70, 1, 8, 3, TOUS, 0, 100};
//description : alterne entre carreaux de gel, de feu, …
weapon_t pistolet_eclectique ={35, 2, 15, 2, ELECTRIQUE, 40, 50};
//description : tir des arcs électrique qui touche tous les ennemie à porter dans la direction de tir
weapon_t pistolet_mitrailleur ={10, 10, 40, 0.5, AUCUN, 25, 50};
//description : tir et recharge vite mais peu de dégats
weapon_t pistolet_jsp_koi ={20, 2, 20, 1.5, AUCUN, 7.5, 100};
//description : tir dans 4 direction 

#endif
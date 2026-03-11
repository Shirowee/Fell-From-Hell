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

extern weapon_t minigun;
//description : tir vite avec dispersion, grand chargeur
extern weapon_t lance_flammes;
//description : peu de dégâts mais brûle
extern weapon_t lance_missile_tete_chercheuse;
//description : lance un missile qui se dirige vers l’ennemi le plus proche, cadence de tir élevée, temps de rechargement long
extern weapon_t fusil_a_pompe;
//description : tir 9 balles en forme de cone
extern weapon_t pistolet_laser;
//description : tir un rayon laser qui reste pendant 1sec
extern weapon_t fusil_rafales;
//description : tir trois balles d’affilées
extern weapon_t lance_glace;
//description : lance flamme mais type gel
extern weapon_t lance_roquette;
//description : tir un missile en ligne droite qui explose au bout de x sec
extern weapon_t epee_longue;
//description : attaque en face avec un grand angle (style reinhardt)
extern weapon_t sniper;
//description : cadence de tir lente et petit chargeur mais grosse balle et bcp de dégâts
extern weapon_t arbalete;
//description : alterne entre carreaux de gel, de feu, …
extern weapon_t pistolet_eclectique;
//description : tir des arcs électrique qui touche tous les ennemie à porter dans la direction de tir
extern weapon_t pistolet_mitrailleur;
//description : tir et recharge vite mais peu de dégats
extern weapon_t pistolet_jsp_koi;
//description : tir dans 4 direction 


//definition des fonction
void PlayerShoot(weapon_t weapon, Vector2 posJoueur, double * time);
void ChangeWeapon(weapon_t * oldWeapon, weapon_t newWeapon);

#endif
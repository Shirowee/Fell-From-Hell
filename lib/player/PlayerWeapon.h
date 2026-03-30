#ifndef PLAYER_WEAPON_H
#define PLAYER_WEAPON_H

#include "../../raylib/include/raylib.h"
#include "../systems/BulletPool.h"


typedef struct Player_s Player;

#define MINIGUN 0
#define LANCE_FLAMEMS 1
#define LANCE_MISSILE_TETE_CHERCHEUSE 2
#define FUSIL_A_POMPE 3
#define PISTOLET_LASER 4
#define FUSIL_RAFALES 5
#define LANCE_GLACE 6
#define LANCE_ROQUETTE 7
#define EPEE_LONGUE 8
#define SNIPER 9
#define ARBALETE 10
#define PISTOLET_ELECTRIQUE 11
#define PISTOLET_MITRAILLEUR 12
#define PISTOLET_MULTI_DIRECTION 13

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
    int indice;                 //indice de l'arme
    float dmg;
    float tps;                  //tir par seconde
    int magazine;               //nombre de munition
    int amo_left;               //nombre de munition restante
    float reloadTime;           //en secondes
    effect_t effet;             //effet de l'arme
    int dispersion;             //rayon de dispersion de l'arme
    float lifeTime;             //durer de vie d'une bullet en sec
    int bulletSpeed;
    int bulletSize;
}weapon_t;


//definition des armes

extern weapon_t minigun;
//description : tir vite avec dispersion, grand chargeur
extern weapon_t lance_flammes;
//description : peu de dégâts mais brûle
extern weapon_t lance_missile_tete_chercheuse;
//description : lance un missile qui se dirige vers l’ennemi le plus proche, cadence de tir élevée, temps de rechargement long
extern weapon_t fusil_a_pompe;
//description : tir 7 balles en forme de cone
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
extern weapon_t pistolet_multi_direction;
//description : tir dans 4 direction 


//definition des fonction
void PlayerShoot(Player* player, double * timeSpent, double * startReload);
void ChangeWeapon(weapon_t * oldWeapon, weapon_t newWeapon);
void spawnBulletWeapon(weapon_t weapon, Vector2 posJoueur, int direction);
int Cooldown(weapon_t weapon, double  * timeSpent);
int IsReloading(weapon_t * weapon, double * startReload);

#endif
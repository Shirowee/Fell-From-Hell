#include "../../raylib/include/raylib.h"

/*
typedef enum{
    AUCUN,
    TOUS,
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
    int porte;                  //porté de l'arme entre 0 et 100
}arme_t;


//definition des armes

arme_t minigun ={12.5, 10, 75, 3, AUCUN, 20, 100};
//description : tir vite avec dispersion, grand chargeur
arme_t lance_flammes ={10, 20, 300, 3, FEU, 30, 20};
//description : peu de dégâts mais brûle
arme_t lance_missile_tete_chercheuse ={125, 2, 10, 6, AUCUN, 0, 100};
//description : lance un missile qui se dirige vers l’ennemi le plus proche, cadence de tir élevée, temps de rechargement long
arme_t fusil_a_pompe ={12.5, 0.5, 6, 5, AUCUN, 50, 20};
//description : tir 9 balles en forme de cone
arme_t pistolet_laser ={50, 0.8, 10, 3, AUCUN, 0, 100};
//description : tir un rayon laser qui reste pendant 1sec
arme_t fusil_rafales ={35, 2, 11, 3, AUCUN, 10, 100};
//description : tir trois balles d’affilées
arme_t lance_glace ={10, 20, 300, 3, GEL, 30, 20};
//description : lance flamme mais type gel
arme_t lance_roquette ={150, 0.8, 8, 4, FEU, 0, 50};
//description : tir un missile en ligne droite qui explose au bout de x sec
arme_t epee_longue ={75, 1.5, -1, -1, AUCUN, 160, 10};
//description : attaque en face avec un grand angle (style reinhardt)
arme_t sniper ={150, 0.5, 6, 3, AUCUN, 0, 100};
//description : cadence de tir lente et petit chargeur mais grosse balle et bcp de dégâts
arme_t arbalete ={70, 1, 8, 3, TOUS, 0, 100};
//description : alterne entre carreaux de gel, de feu, …
arme_t pistolet_eclectique ={35, 2, 15, 2, ELECTRIQUE, 40, 50};
//description : tir des arcs électrique qui touche tous les ennemie à porter dans la direction de tir
arme_t pistolet_mitrailleur ={10, 10, 40, 0.5, AUCUN, 25, 50};
//description : tir et recharge vite mais peu de dégats
arme_t pistolet_jsp_koi ={20, 2, 20, 1.5, AUCUN, 7.5, 100};
//description : tir dans 4 direction 

*/
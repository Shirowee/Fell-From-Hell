/**
 * \file PlayerMovement.h
 * \brief Gestion des armes du joueur (tir, rechargement, types d'armes).
 * \author Kilian
 */

#ifndef PLAYER_WEAPON_H
#define PLAYER_WEAPON_H

#include "../../raylib/include/raylib.h"
#include "../systems/BulletPool.h"

/**
 * \brief Structure opaque représentant le joueur.
 */
typedef struct Player_s Player;

/* =========================
 * Constantes des armes
 * ========================= */

/** \def MINIGUN */
#define MINIGUN 0
/** \def LANCE_FLAMMES */
#define LANCE_FLAMMES 1
/** \def LANCE_MISSILE_TETE_CHERCHEUSE */
#define LANCE_MISSILE_TETE_CHERCHEUSE 2
/** \def FUSIL_A_POMPE */
#define FUSIL_A_POMPE 3
/** \def PISTOLET_LASER */
#define PISTOLET_LASER 4
/** \def FUSIL_RAFALES */
#define FUSIL_RAFALES 5
/** \def LANCE_GLACE */
#define LANCE_GLACE 6
/** \def LANCE_ROQUETTE */
#define LANCE_ROQUETTE 7
/** \def EPEE_LONGUE */
#define EPEE_LONGUE 8
/** \def SNIPER */
#define SNIPER 9
/** \def ARBALETE */
#define ARBALETE 10
/** \def PISTOLET_ELECTRIQUE */
#define PISTOLET_ELECTRIQUE 11
/** \def PISTOLET_MITRAILLEUR */
#define PISTOLET_MITRAILLEUR 12
/** \def PISTOLET_MULTI_DIRECTION */
#define PISTOLET_MULTI_DIRECTION 13

/* =========================
 * Types d'effets
 * ========================= */

/**
 * \enum effect_t
 * \brief Types d'effets applicables aux armes.
 */
typedef enum{
    AUCUN,         /**< Aucun effet */
    TOUS,          /**< Tous les effets */
    FEU,           /**< Brûlure */
    GEL,           /**< Gel */
    ELECTRIQUE,    /**< Électricité */
    MALEDICTION,   /**< Malédiction */
    BENEDICTION    /**< Bénédiction */
} effect_t;

/* =========================
 * Structure arme
 * ========================= */

/**
 * \struct weapon_t
 * \brief Structure représentant une arme.
 */
typedef struct{
    int indice;             /**< Identifiant de l'arme */
    float dmg;              /**< Dégâts infligés */
    float tps;              /**< Tirs par seconde */
    int magazine;           /**< Capacité du chargeur */
    int amo_left;           /**< Munitions restantes */
    float reloadTime;       /**< Temps de rechargement (secondes) */
    effect_t effet;         /**< Effet appliqué */
    int dispersion;         /**< Dispersion du tir */
    float lifeTime;         /**< Durée de vie des projectiles (secondes) */
    int bulletSpeed;        /**< Vitesse des projectiles */
    int bulletSize;         /**< Taille des projectiles */
} weapon_t;

/* =========================
 * Déclarations des armes
 * ========================= */

/** \brief Minigun : tir rapide avec dispersion et grand chargeur */
extern weapon_t minigun;

/** \brief Lance-flammes : faibles dégâts mais applique brûlure */
extern weapon_t lance_flammes;

/** \brief Lance-missile à tête chercheuse */
extern weapon_t lance_missile_tete_chercheuse;

/** \brief Fusil à pompe : tir en cône de plusieurs projectiles */
extern weapon_t fusil_a_pompe;

/** \brief Pistolet laser : rayon continu pendant 1 seconde */
extern weapon_t pistolet_laser;

/** \brief Fusil à rafales : tir de 3 balles successives */
extern weapon_t fusil_rafales;

/** \brief Lance-glace : équivalent gel du lance-flammes */
extern weapon_t lance_glace;

/** \brief Lance-roquette : missile explosif */
extern weapon_t lance_roquette;

/** \brief Épée longue : attaque de mêlée en cône */
extern weapon_t epee_longue;

/** \brief Sniper : tir lent mais très puissant */
extern weapon_t sniper;

/** \brief Arbalète : alterne différents types de carreaux */
extern weapon_t arbalete;

/** \brief Pistolet électrique : attaque en chaîne les ennemis proches */
extern weapon_t pistolet_eclectique;

/** \brief Pistolet mitrailleur : rapide mais peu puissant */
extern weapon_t pistolet_mitrailleur;

/** \brief Pistolet multidirection : tir dans 4 directions */
extern weapon_t pistolet_multi_direction;

/* =========================
 * Fonctions
 * ========================= */

/**
 * \brief Permet au joueur de tirer avec son arme actuelle.
 * \param player Pointeur vers le joueur
 * \param timeSpent Temps écoulé depuis le dernier tir
 * \param startReload Temps de début du rechargement
 */
void PlayerShoot(Player* player, double *timeSpent, double *startReload);

/**
 * \brief Change l'arme actuelle.
 * \param oldWeapon Pointeur vers l'arme actuelle
 * \param indice Indice de la nouvelle arme à équiper
 */
void ChangeWeapon(weapon_t *oldWeapon, int indice);

/**
 * \brief Génère un projectile selon les caractéristiques de l'arme.
 * \param weapon Arme utilisée
 * \param posJoueur Position du joueur
 * \param direction Direction du tir
 */
void spawnBulletWeapon(weapon_t weapon, Player player, int direction);

/**
 * \brief Vérifie si l'arme est en cooldown.
 * \param weapon Arme utilisée
 * \param timeSpent Temps écoulé
 * \return 1 si en cooldown, 0 sinon
 */
int Cooldown(weapon_t weapon, double *timeSpent);

/**
 * \brief Vérifie si l'arme est en cours de rechargement.
 * \param weapon Arme concernée
 * \param startReload Temps de début du rechargement
 * \return 1 si en rechargement, 0 sinon
 */
int IsReloading(weapon_t *weapon, double *startReload);

#endif
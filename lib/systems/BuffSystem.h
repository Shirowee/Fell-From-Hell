/**
 * \file BuffSystem.h
 * \brief Gestion des améliorations (buffs) appliquées au joueur et aux armes.
 * \author Kilian
 */

#ifndef BUFFSYSTEM_H
#define BUFFSYSTEM_H

#include "../../raylib/include/raylib.h"

/**
 * \struct buff_t
 * \brief Représente un ensemble de bonus appliqués aux caractéristiques du joueur ou des armes.
 */
typedef struct {
    /* ===== Buffs mineurs ===== */
    float dmg;           /**< Bonus de dégâts */
    float fireRate;      /**< Bonus de cadence de tir */
    float reloadTime;    /**< Réduction du temps de rechargement */
    float dispersion;    /**< Réduction de la dispersion */
    float bulletSpeed;   /**< Augmentation de la vitesse des projectiles */
    float bulletSize;    /**< Augmentation de la taille des projectiles */

    /*
     * ===== Buffs avancés (non utilisés actuellement) =====
     *
     * effect_t effet;     // Effet appliqué (feu, gel, etc.)
     * float fireDmg;      // Dégâts de brûlure
     * float iceTime;      // Durée de gel
     * float movementSpeed;// Vitesse de déplacement
     * float dashCooldown; // Temps de recharge du dash
     *
     * ===== Buffs majeurs =====
     * int extraDash;      // Nombre de dash supplémentaires
     */
} buff_t;

/* =========================
 * Fonctions de modification des buffs
 * ========================= */

/**
 * \brief Augmente les dégâts.
 * \param buff Pointeur vers la structure de buff
 * \param add Valeur à ajouter
 */
void BuffDmg(buff_t* buff, float add);

/**
 * \brief Augmente la cadence de tir.
 * \param buff Pointeur vers la structure de buff
 * \param add Valeur à ajouter
 */
void BufffireRate(buff_t* buff, float add);

/**
 * \brief Réduit le temps de rechargement.
 * \param buff Pointeur vers la structure de buff
 * \param sub Valeur à soustraire
 */
void BuffreloadTime(buff_t* buff, float sub);

/**
 * \brief Réduit la dispersion des tirs.
 * \param buff Pointeur vers la structure de buff
 * \param sub Valeur à soustraire
 */
void Buffdispersion(buff_t* buff, float sub);

/**
 * \brief Augmente la vitesse des projectiles.
 * \param buff Pointeur vers la structure de buff
 * \param add Valeur à ajouter
 */
void BuffbulletSpeed(buff_t* buff, float add);

/**
 * \brief Augmente la taille des projectiles.
 * \param buff Pointeur vers la structure de buff
 * \param add Valeur à ajouter
 */
void BuffbulletSize(buff_t* buff, float add);

/**
 * \brief Initialise et alloue un nouveau buff.
 * \return Pointeur vers une structure buff_t initialisée
 *
 * \note Les valeurs du buff sont initialisées à 1 (aucun bonus).
 * \warning La mémoire allouée doit être libérée avec FreeBuff().
 */
buff_t* BuffInit(void);

/**
 * \brief Libère les ressources associées à un buff.
 * \param buff Pointeur vers la structure de buff à libérer
 */
void FreeBuff(buff_t* buff);

#endif
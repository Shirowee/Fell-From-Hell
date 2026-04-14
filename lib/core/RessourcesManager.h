/**
 * @file RessourcesManager.h
 * @brief Gestion centralisée des ressources du jeu (textures et sons)
 *
 * Ce module permet de charger, stocker et gérer les ressources du jeu
 * de manière centralisée afin d’éviter les doublons et optimiser la mémoire.
 *
 * Les ressources sont identifiées via des enums (TextureID / SoundID),
 * garantissant un accès rapide et sécurisé sans utilisation de chemins strings.
 *
 * Fonctionnalités :
 * - Chargement lazy ou global des ressources
 * - Accès rapide via identifiants (enum)
 * - Gestion du cache mémoire
 * - Gestion du volume global des effets sonores
 *
 * @author A. Pocholle
 */

#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include "../../raylib/include/raylib.h"
#include <stdbool.h>

/* =========================================================
   TEXTURES
   ========================================================= */

/**
 * @brief Identifiants des textures du jeu
 *
 * Chaque enum correspond à une texture chargée en mémoire.
 * L’ordre doit correspondre au tableau interne texturePaths.
 */
typedef enum {
    TEX_PLAYER,
    TEX_BACKGROUND_NEBULA,
    TEX_TITLE,
    TEX_COUNT
} TextureID;

/**
 * @brief Récupère une texture du gestionnaire
 *
 * Charge la texture si nécessaire, sinon retourne celle en cache.
 *
 * @param id Identifiant de la texture
 * @return Pointeur vers la texture chargée
 */
Texture2D* RM_GetTexture(TextureID id);


/* =========================================================
   SOUNDS
   ========================================================= */

/**
 * @brief Identifiants des effets sonores du jeu
 *
 * Chaque enum correspond à un son chargé en mémoire.
 * L’ordre doit correspondre au tableau interne soundPaths.
 */
typedef enum {
    SND_DASH,
    SND_ENEMY_DIE,
    SND_ENEMY_HURT,
    SND_ENEMY_SHOOT,
    SND_HURT,
    SND_JUMP,
    SND_SHOOT,
    SND_SELECT,
    SND_SELECTED,
    SND_COUNT
} SoundID;

/**
 * @brief Récupère un son du gestionnaire
 *
 * Charge le son si nécessaire, sinon retourne celui en cache.
 *
 * @param id Identifiant du son
 * @return Pointeur vers le son chargé
 */
Sound* RM_GetSound(SoundID id);

/**
 * @brief Joue un effet sonore
 *
 * Applique automatiquement le volume global avant lecture.
 *
 * @param id Identifiant du son à jouer
 */
void RM_PlaySound(SoundID id);


/* =========================================================
   VOLUME
   ========================================================= */

/**
 * @brief Définit le volume global des effets sonores
 *
 * @param volume Valeur entre 0.0 (silence) et 1.0 (max)
 */
void RM_SetSFXVolume(float volume);

/**
 * @brief Récupère le volume global actuel
 *
 * @return Volume des SFX (0.0 - 1.0)
 */
float RM_GetSFXVolume(void);


/* =========================================================
   GLOBAL
   ========================================================= */

/**
 * @brief Charge toutes les ressources du jeu
 *
 * Précharge textures et sons pour éviter les stutters en jeu.
 */
void RM_LoadAll(void);

/**
 * @brief Libère toutes les ressources du jeu
 *
 * Doit être appelé à la fin du programme pour éviter les leaks mémoire.
 */
void RM_UnloadAll(void);

/**
 * @brief Affiche l’état du Resource Manager (debug)
 *
 * Affiche dans la console :
 * - textures chargées
 * - sons chargés
 * - état interne
 */
void RM_PrintStatus(void);

#endif // RESOURCES_MANAGER_H
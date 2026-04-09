/**
 * \file Screen.h
 * \brief Définition des différents écrans du jeu (menu, jeu, paramètres, sortie).
 * \author Kilian
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "../player/Player.h"

/**
 * \enum Screen_t
 * \brief Représente les différents états/écrans du jeu.
 */
typedef enum {
    SCREEN_MENU,      /**< Écran du menu principal */
    SCREEN_GAME,      /**< Écran de jeu */
    SCREEN_SETTINGS,  /**< Écran des paramètres */
    SCREEN_PAUSE,     /**< Écran de pause */
    SCREEN_END_LEVEL, /**< Écran de fin d'un niveau */
    SCREEN_EXIT       /**< Quitte le jeu */
} Screen_t;

/* =========================
 * Fonctions de gestion des écrans
 * ========================= */

/**
 * \brief Met à jour le menu principal.
 * \return Le prochain écran à afficher (Screen_t)
 *
 * \details Gère les entrées utilisateur (clavier/souris) et
 * permet de naviguer entre les options (jouer, paramètres, quitter).
 */
Screen_t MenuUpdate(void);

/**
 * \brief Lance et met à jour la logique du jeu.
 * \return Le prochain écran à afficher (Screen_t)
 *
 * \details Contient la boucle ou la logique principale du gameplay.
 * Peut retourner SCREEN_MENU ou SCREEN_EXIT selon les actions du joueur.
 */
Screen_t Game(Player* player);

/**
 * \brief Met à jour l'écran des paramètres.
 * \return Le prochain écran à afficher (Screen_t)
 *
 * \details Permet de modifier les options du jeu (audio, contrôles, etc.).
 */
Screen_t SettingsUpdate(Screen_t previousScreen);

/**
 * \brief Met à jour l'écran de pause.
 * \return Le prochain écran à afficher (Screen_t)
 *
 * \details Gère les interactions durant la pause (reprendre la partie,
 * modifier les paramètres, quitter le jeu, etc.).
 */
Screen_t PauseUpdate(void);

/**
 * \brief Met à jour l'écran de fin de niveau.
 * \return Le prochain écran à afficher (Screen_t)
 *
 * \details Affiche les résultats du niveau et permet au joueur d'obtenir 
 * des améliorations de passer au niveau suivant ou de quitter le jeu.
 */
Screen_t EndLevelUpdate(Player* player);

/**
 * \brief Gère l'état de déclenchement d'un nouveau niveau.
 * \param newFlag Indique si un changement d'état est demandé (1 = toggle, 0 = aucun changement)
 * \return L'état actuel du nouveau niveau (1 = actif, 0 = inactif)
 *
 * \details
 * Cette fonction utilise une variable statique pour mémoriser l'état entre les appels.
 * Si \p newFlag est à 1, l'état est inversé (toggle).
 * Si \p newFlag est à 0, l'état reste inchangé.
 *
 * \note Fonctionne comme un interrupteur (toggle).
 */
int NewLevel(int newFlag);

#endif
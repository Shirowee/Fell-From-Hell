/**
 * \file Screen.h
 * \brief Définition des différents écrans du jeu (menu, jeu, paramètres, sortie).
 * \author Kilian
 */

#ifndef SCREEN_H
#define SCREEN_H

/**
 * \enum Screen_t
 * \brief Représente les différents états/écrans du jeu.
 */
typedef enum {
    SCREEN_MENU,      /**< Écran du menu principal */
    SCREEN_GAME,      /**< Écran de jeu */
    SCREEN_SETTINGS,  /**< Écran des paramètres */
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
Screen_t Game(void);

/**
 * \brief Met à jour l'écran des paramètres.
 * \return Le prochain écran à afficher (Screen_t)
 *
 * \details Permet de modifier les options du jeu (audio, contrôles, etc.).
 */
Screen_t SettingsUpdate(void);


#endif
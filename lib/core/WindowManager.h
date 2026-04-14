/**
 * \file WindowManager.h
 * \author Thomas
 * \brief Gestionnaire de la fenêtre de jeu et de l'affichage de la fenêtre
 * * Ce fichier gère l'initialisation de la fenêtre Raylib ainsi que la gestion du pleine écran en
 * fonction du système d'exploitation
 */

#ifndef WINDOW_MANAGER
#define WINDOW_MANAGER_H

/**
 * @brief Vérifie et change l'état de premier plan de la fenêtre
 * * Si la fenêtre est sélectionnée elle est forcée au premier plan
 * Si elle n'est plus sélectionnée alors on enlève le flag forçant la mise au premier plan
 */
bool verifPremPlan(void);

/**
 * @brief Initialise la fenêtre de jeu
 * * Initialise la fenêtre de jeu caché le temps de l'ouverture puis visible à la taille 
 * de l'écran mais sans la barre de titre
 * @note Sur Windows on met un pixel de moins pour éviter un bug d'affichage
 */
void WindowInit();

/**
 * @brief Met à jour la fenêtre à chaque frame
 */
void WindowManager_Update(void);

/**
 * @brief Récupère l'état actuel en premier plan ou non de la fenêtre
 * @return true si la fenêtre est actuellement au premier plan, false sinon.
 */
bool WindowManager_IsTopmost(void);

#endif
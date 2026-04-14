/**
 * @file RessourcesManager.c
 * @brief Gestion des ressources du jeu
 * 
 * Définit l’interface de gestion des ressources du jeu, y compris
 * les textures, sons et autres éléments graphiques.
 *
 * Fournit des fonctions pour :
 * - charger les ressources
 * - libérer les ressources
 * - accéder aux ressources
 *
 * @author A. Pocholle
 */

#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include "../../raylib/include/raylib.h"
/**
 * @brief Récupère une texture depuis le gestionnaire
 * 
 * Si la texture est déjà chargée, elle est simplement retournée.
 * Sinon, elle est chargée puis stockée.
 * 
 * @param path Chemin vers le fichier image
 * @return Pointeur vers la texture, ou NULL en cas d'erreur
 * 
 * @note La texture reste en mémoire jusqu'à appel de RM_UnloadTexture()
 * ou RM_UnloadAll()
 */
Texture2D* RM_GetTexture(const char *path);

/**
 * @brief Décharge une texture spécifique
 * 
 * Libère la mémoire GPU associée à la texture et la retire
 * du gestionnaire.
 * 
 * @param path Chemin de la texture à libérer
 * 
 * @warning Si la texture n'existe pas, la fonction ne fait rien
 */
void RM_UnloadTexture(const char *path);

/**
 * @brief Décharge toutes les textures
 * 
 * Libère toutes les textures chargées en mémoire GPU
 * et réinitialise le gestionnaire.
 * 
 * @warning Doit être appelé avant la fermeture du programme
 */
void RM_UnloadAll(void);

/**
 * @brief Affiche l'état interne du Resource Manager (debug)
 * 
 * Affiche dans la console :
 * - le nombre de textures chargées
 * - la liste des chemins
 */
void RM_PrintStatus(void);



#endif // RESOURCES_MANAGER_H
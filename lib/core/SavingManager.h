/**
 * \file SavingManager.h
 * \author Thomas
 * \brief Sert a enregistrer différentes informations pour pouvoir reprendre une partie
 * Ce fichier créer un fichier contenant les informations nécessaire pour reprendre une partie
 * en cours de déroulement
 */


#ifndef SAVING_MANAGER_H
#define SAVING_MANAGER_H

#include <stdbool.h>
#include "../player/Player.h"
#include "../systems/BuffSystem.h"
#include "../player/PlayerWeapon.h"

/**
 * @struct SaveData_t
 * @brief Données sauvegardées pour reprendre une partie
 */
typedef struct {
    char mapId[32];         /**< Identifiant de la map courante */
    weapon_t weapon;        /**< Arme actuellement équipée */
    buff_t buff;            /**< Buffs actifs du joueur */
    float difficultyMultHP; /**< Multiplicateur de difficulté (HP ennemis) */
    float difficultyMultDMG;/**< Multiplicateur de difficulté (dégâts ennemis) */
} SaveInfo;

/**
 * @brief Sauvegarde l'état actuel du jeu dans un fichier
 * @param player Pointeur vers le joueur courant
 */
void SaveGame(Player *player);

/**
 * @brief Charge un fichier de sauvegarde et applique les données au joueur
 * @param player Pointeur vers le joueur à initialiser
 * @return true si le chargement a réussi, false sinon
 */
bool LoadGame(Player *player);

/**
 * @brief Vérifie si un fichier de sauvegarde existe
 * @return true si une sauvegarde est disponible, false sinon
 */
bool HasSaveFile(void);

/**
 * @brief Supprime le fichier de sauvegarde
 */
void DeleteSave(void);

#endif

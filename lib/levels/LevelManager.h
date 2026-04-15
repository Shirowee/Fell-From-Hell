/**
 * \file LevelManager.h
 * \author Thomas
 * \brief Ce fichier LevelManager.h sert a la gestion des niveaux (affichage et chargement)
 * 
 * * LevelManager permet de transformer un fichier JSON contenant toutes les informations sur une map 
 * et converti toute ces informations en une structure viable en C pour réaliser l'affichage et permettre la 
 * réalisation de tout ce qui touche a la map
 */

#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "Platform.h"
#include "../player/Player.h"
#include "../systems/BulletPool.h"
#include "../systems/EnemyPool.h"
#include "../systems/EnemySpawner.h"
#include "../../lib/cJson/cJSON.h"
#include "../../lib/systems/ParallaxSystem.h"


/** @name Maximum de tout les éléments d'une map
 * @{ */
#define MAX_PLATFORMS 100   /**< Nombre maximum de plateformes par map */
#define MAX_ENEMIES 50      /**< Nombre maximum d'ennemis par map */
#define MAX_HAZARDS 50      /**< Nombre maximum de pièges par map */
#define MAX_TRIGGERS 20     /**< Nombre maximum de zone provoquant un événement par map */
/** @} */


/**
 * @struct MapInfo
 * @brief Informations globales sur le niveau
 */
typedef struct {
    char id[32];        /**< Identifiant de la map*/
    char title[64];     /**< Nom de la map*/
    int width;          /**< Largeur totale de la map (en pixel "fixe")*/
    int height;         /**< Hauteur totale de la map (en pixel "fixe")*/
} MapInfo;

/**
 * @struct Enemy
 * @brief Informations sur les vagues d'ennemis
 */
typedef struct {
    int nbType;        /**< Numéro du patern de la vague d'ennemis*/
    float spawnTime;      /**< Temps avant l'apparition de la prochaine vague d'ennemis*/
    Pos position;       /**< Position d'apparition de la vague*/
    bool spawned;
} Enemy;

/**
 * @struct Hazard
 * @brief Informations sur les pièges du niveau
 */
typedef struct {
    char type[32];      /**< Type / Nom du piège */
    Pos position;       /**< Variable contenant les coordonnées (x et y) du piège*/
} Hazard;

/**
 * @struct Hazard
 * @brief Informations sur les zones provoquant un événement
 */
typedef struct {
    char id[32];        /**< Identifiant de la zone*/
    Rect rect;          /**< Variable contenant toutes les informations sur la taille et les coordonnées de la zone*/
    char action[32];    /**< Nom de l'action qui doit être réalisé dans cette zone*/
    bool triggered;      /**< Booleen pour savoir si le trigger a déjà été éxécuté*/
} Trigger;


/**
 * @struct Level
 * @brief Structute globale qui contient toutes les informations sur le niveau
 */
typedef struct {
    MapInfo info;       /**< Informations globales sur la map*/
    

    Platform platforms[MAX_PLATFORMS];      /**< Tableau des plateformes */
    int platformCount;                      /**< Nombre de platformes la map */


    Pos playerStart;                /**< Coordonnées de départ du joueur */

    Enemy enemies[MAX_ENEMIES];     /**< Tableau des ennemis */
    int enemyCount;                 /**< Nombre de type d'enemi sur la map */

    Hazard hazards[MAX_HAZARDS];    /**< Tableau des pièges */
    int hazardCount;                /**< Nombre actuel de piège sur la map */

    Trigger triggers[MAX_TRIGGERS]; /**< Tableau de zone provoquant un événement */
    int triggerCount;               /**< Nombre actuel de zone provoquant un événement */

    ParallaxSystem parallax;
} Level;


/**
 * @brief Organise les données chargé a partir du JSON dans une structure niveau
 * @param json Qui contient les données extrait par la fonction readJsonLvl
 * @param lvl Qui correspond au niveau dans lequel les informations vont être organisé
 */
void parseLevelData(cJSON *json, Level *lvl);


/**
 * @brief Charge les données d'un niveau depuis un fichier JSON
 * @param fileName Nom du fichier à lire (sans le .json)
 * @return Retourne 1 si succès, 0 ou -1 en cas d'erreur de lecture
 */
int readJsonLvl(const char * fileName);


/**
 * @brief Initialise le niveau après la conversion JSON
 */
void LevelInit(void);

/**
 * @brief Traduit les plateformes en tiles et les dessine
 * @param p Plateforme à dessiner
 * @param tileset Texture contenant les tiles à utiliser pour dessiner la plateforme
 */
void BuildTilesFromPlatforms(void);

/**
 * @brief Dessine les platformes et le décors du niveau
 */
void LevelDraw(void);


/**
 * \param targetId Nom de la map vers laquelle on se dirige
 */
void NextLvlRequest(const char *targetId);


/**
 * \brief Réalise le passage au niveau suivant
 */
void NextLvlUpdate(Player *player, enemyPool_t *enemyPool, bulletPool_t *bulletPool, EnemySpawner *enemySpawner);

/**
 *  @brief Contient toutes les informations sur le niveau actuel
 */
extern Level currentLevel; 

#endif

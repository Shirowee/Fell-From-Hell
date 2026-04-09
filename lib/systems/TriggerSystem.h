#ifndef TRIGGER_SYSTEM_H
#define TRIGGER_SYSTEM_H

#include "../levels/LevelManager.h"
#include "../player/Player.h"


/**
 * \brief Vérifie si le joueur est dans le rayon d'un trigger exécute l'action associés si oui
 * \param player Pointeur sur le joueur
 * \param level  Pointeur sur le niveau
 */
void TriggerSystemUpdate(Player *player, Level *level);


/**
 * \brief Exécute l'action associée à un trigger
 * \param trigger Pointeur sur un trigger
 * \param level   Pointeur sur le niveau
 */
void TriggerExecute(Trigger *trigger, Level *level);

#endif
#include "../../lib/systems/TriggerSystem.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/levels/LevelManager.h"
#include <string.h>
#include <stdio.h>

void TriggerExecute(Trigger *trigger, Level *level) {
    if (strcmp(trigger->id, "finNiveau") == 0) {
        LevelTransitionRequest(trigger->action);
    }
}


void TriggerSystemUpdate(Player *player, Level *level) {
    Rectangle playerRect = player->body.main;

    for (int i = 0; i < level->triggerCount; i++) {
        Trigger *trigger = &level->triggers[i];

        Rectangle trigRect = {
            trigger->rect.x,
            trigger->rect.y,
            trigger->rect.w,
            trigger->rect.h
        };

        if (CheckCollisionRecs(playerRect, trigRect)) {
            TriggerExecute(trigger, level);
        }
    }
}
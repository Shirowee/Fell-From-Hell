#include "../../lib/levels/LevelManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/cJson/cJSON.h"
#include "../../lib/player/PlayerController.h"
#include "../../lib/systems/EnemyPool.h"
#include "../../lib/systems/BulletPool.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Level currentLevel = {0};


void parseLevelData(cJSON *json, Level *lvl) {
    if (json == NULL || lvl == NULL) return;

    // 1. Extraction de map_info
    cJSON *map_info = cJSON_GetObjectItemCaseSensitive(json, "map_info");
    if (map_info) {
        cJSON *id = cJSON_GetObjectItemCaseSensitive(map_info, "id");
        cJSON *title = cJSON_GetObjectItemCaseSensitive(map_info, "title");
        cJSON *dims = cJSON_GetObjectItemCaseSensitive(map_info, "dimensions");

        if (cJSON_IsString(id)) strncpy(lvl->info.id, id->valuestring, 31);
        if (cJSON_IsString(title)) strncpy(lvl->info.title, title->valuestring, 63);
        if (dims) {
            lvl->info.width = cJSON_GetObjectItemCaseSensitive(dims, "w")->valueint;
            lvl->info.height = cJSON_GetObjectItemCaseSensitive(dims, "h")->valueint;
        }
    }

    // 2. Extraction des Plateformes
    cJSON *platforms = cJSON_GetObjectItemCaseSensitive(json, "platforms");
    lvl->platformCount = 0;
    cJSON *plat = NULL;
    cJSON_ArrayForEach(plat, platforms) {
        if (lvl->platformCount < MAX_PLATFORMS) {
            Platform *p = &lvl->platforms[lvl->platformCount];
            strncpy(p->type, cJSON_GetObjectItemCaseSensitive(plat, "type")->valuestring, 31);
            p->solid = cJSON_GetObjectItemCaseSensitive(plat, "solid")->valueint;
            p->x = (float)cJSON_GetObjectItemCaseSensitive(plat, "x")->valuedouble;
            p->y = (float)cJSON_GetObjectItemCaseSensitive(plat, "y")->valuedouble;
            p->width = (float)cJSON_GetObjectItemCaseSensitive(plat, "width")->valuedouble;
            p->high = (float)cJSON_GetObjectItemCaseSensitive(plat, "high")->valuedouble;
            lvl->platformCount++;
        }
    }

    // 3. Extraction des Entités
    cJSON *entities = cJSON_GetObjectItemCaseSensitive(json, "entities");
    if (entities) {
        // Player Start
        cJSON *p_start = cJSON_GetObjectItemCaseSensitive(entities, "player_start");
        if (p_start) {
            lvl->playerStart.x = cJSON_GetObjectItemCaseSensitive(p_start, "x")->valueint;
            lvl->playerStart.y = cJSON_GetObjectItemCaseSensitive(p_start, "y")->valueint;
        }

        // Enemies
        cJSON *enemies = cJSON_GetObjectItemCaseSensitive(entities, "enemies");
        lvl->enemyCount = 0;
        cJSON *en = NULL;
        cJSON_ArrayForEach(en, enemies) {
            if (lvl->enemyCount < MAX_ENEMIES) {
                Enemy *e = &lvl->enemies[lvl->enemyCount];
                e->nbType = cJSON_GetObjectItemCaseSensitive(en, "nbType")->valueint;
                e->spawnTime = cJSON_GetObjectItemCaseSensitive(en, "spawnTime")->valuedouble;
                
                cJSON *pos = cJSON_GetObjectItemCaseSensitive(en, "position");
                e->position.x = cJSON_GetObjectItemCaseSensitive(pos, "x")->valueint; 
                e->position.y = cJSON_GetObjectItemCaseSensitive(pos, "y")->valueint;
                
                lvl->enemyCount++;
                e->spawned = false;
            }
        }

        // Hazards
        cJSON *hazards = cJSON_GetObjectItemCaseSensitive(entities, "hazards");
        lvl->hazardCount = 0;
        cJSON *hz = NULL;
        cJSON_ArrayForEach(hz, hazards) {
            if (lvl->hazardCount < MAX_HAZARDS) {
                strncpy(lvl->hazards[lvl->hazardCount].type, cJSON_GetObjectItemCaseSensitive(hz, "type")->valuestring, 31);
                lvl->hazards[lvl->hazardCount].position.x = cJSON_GetObjectItemCaseSensitive(hz, "x")->valueint;
                lvl->hazards[lvl->hazardCount].position.y = cJSON_GetObjectItemCaseSensitive(hz, "y")->valueint;
                lvl->hazardCount++;
            }
        }
    }

    // 4. Extraction des Triggers
    cJSON *triggers = cJSON_GetObjectItemCaseSensitive(json, "triggers");
    lvl->triggerCount = 0;
    cJSON *trig = NULL;
    cJSON_ArrayForEach(trig, triggers) {
        if (lvl->triggerCount < MAX_TRIGGERS) {
            Trigger *t = &lvl->triggers[lvl->triggerCount];
            strncpy(t->id, cJSON_GetObjectItemCaseSensitive(trig, "id")->valuestring, 31);
            strncpy(t->action, cJSON_GetObjectItemCaseSensitive(trig, "action")->valuestring, 31);
            
            cJSON *r = cJSON_GetObjectItemCaseSensitive(trig, "rect");
            t->rect.x = (float)cJSON_GetObjectItemCaseSensitive(r, "x")->valuedouble;
            t->rect.y = (float)cJSON_GetObjectItemCaseSensitive(r, "y")->valuedouble;
            t->rect.w = (float)cJSON_GetObjectItemCaseSensitive(r, "w")->valuedouble;
            t->rect.h = (float)cJSON_GetObjectItemCaseSensitive(r, "h")->valuedouble;
            lvl->triggerCount++;
            t->triggered = false;
        }
    }
}


int readJsonLvl(const char * fileName){
    const char * path = TextFormat("../lib/map/%s.json",fileName); // Création du chemin complet jusqu'à la map choisi 

    FILE * f = fopen(path,"rb");
    if(f == NULL) {printf("Impossible d'ouvrir le fichier"); return 0;}

    // Lecture du fichier JSON
    char buffer[4096];
    int bytesRead = fread(buffer, 1, sizeof(buffer) - 1, f);

    buffer[bytesRead] = '\0';
    fclose(f);

    cJSON *json = cJSON_Parse(buffer);
    if(json == NULL){
        const char *errorPtr = cJSON_GetErrorPtr();
        if (errorPtr != NULL) { // Aide pour débuguer le JSON s'il y a une erreur
            printf("Erreur: %s\n", errorPtr);
        }
        return 0;
    }

    parseLevelData(json, &currentLevel);
    

    cJSON_Delete(json);

    printf("Titre charge : %s\n", currentLevel.info.title);
    printf("Nombre de plateformes : %d\n", currentLevel.platformCount);

    
    return 1;
}


//Initialise le niveau
void LevelInit(){
    for (int i = 0; i < currentLevel.platformCount; i++) {
        Platform *p = &currentLevel.platforms[i];
        p->rect = (Rectangle){ 
            p->x,
            p->y, 
            p->width, 
            p->high 
        };

        p->color = p->solid ? DARKGRAY : GRAY; // TEMPORAIRE POUR TEST LES DIFFERENT TYPES
        if (strcmp(p->type, "BASIC_PLATFORM_S") == 0) p->color = DARKBLUE; // TEMPORAIRE POUR TEST LES DIFFERENT TYPES
    }
}


//Dessine le niveau
void LevelDraw(void) {
    for (int i = 0; i < currentLevel.platformCount; i++) {
        DrawRectangleRec(currentLevel.platforms[i].rect, currentLevel.platforms[i].color);
    }
}




static char pendingLevel[64] = "";

void NextLvlRequest(const char *targetId) {
    // Evite des problèmes de si ça s'éxécute deux fois
    if (pendingLevel[0] != '\0') return; 
    
    strncpy(pendingLevel, targetId, 63);
    pendingLevel[63] = '\0';
}

void NextLvlUpdate(Player *player, enemyPool_t *enemyPool, bulletPool_t *bulletPool) {
    // Evite des problèmes de si ça s'éxécute deux fois
    if (pendingLevel[0] == '\0') return;

    // Suppression des balles et ennemis
    for (int i = 0; i < enemyPool->capacity; i++)  enemyPool->tab[i].active = 0;
    for (int i = 0; i < bulletPool->capacity; i++)  bulletPool->tab[i].active = 0;

    // Chargement de la nouvelle map
    if (readJsonLvl(pendingLevel)) {
        LevelInit();

        // Reset du joueur
        player->position.x = (float)currentLevel.playerStart.x;
        player->position.y = (float)currentLevel.playerStart.y;
    }

    pendingLevel[0] = '\0';
}

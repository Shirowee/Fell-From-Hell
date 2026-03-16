#include "../raylib/include/raylib.h"
#include "../lib/cJson/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sous Structure
typedef struct {
    int x;
    int y;
} Pos;

typedef struct {
    float x, y, w, h;
} Rect;

// Structures du contenu de la Map
typedef struct {
    char id[32];
    char title[64];
    int width;
    int height;
} MapInfo;

typedef struct {
    char type[32];
    int solid; // 1 pour vrai, 0 pour faux
    float x, y, width, high;
    Rectangle rect; 
    Color color;

} Platform;

typedef struct {
    char type[32];
    float dist_aggro;
} Enemy;

typedef struct {
    char type[32];
    Pos position;
} Hazard;

typedef struct {
    char id[32];
    Rect rect;
    char action[32];
} Trigger;

// Structure Final du niveau
#define MAX_PLATFORMS 100
#define MAX_ENEMIES 50
#define MAX_HAZARDS 50
#define MAX_TRIGGERS 20

typedef struct {
    MapInfo info;
    
    // Plateformes
    Platform platforms[MAX_PLATFORMS];
    int platformCount;

    // Entités
    Pos playerStart;
    Enemy enemies[MAX_ENEMIES];
    int enemyCount;
    Hazard hazards[MAX_HAZARDS];
    int hazardCount;

    // Triggers
    Trigger triggers[MAX_TRIGGERS];
    int triggerCount;
} Level;


Level currentLevel; // Déclaration du niveau


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

    // 2. Extraction des Plateformes (Tableau)
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

    // 3. Extraction des Entités (Player Start, Enemies, Hazards) ---
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
                strncpy(lvl->enemies[lvl->enemyCount].type, cJSON_GetObjectItemCaseSensitive(en, "type")->valuestring, 31);
                lvl->enemies[lvl->enemyCount].dist_aggro = (float)cJSON_GetObjectItemCaseSensitive(en, "dist_aggro")->valuedouble;
                lvl->enemyCount++;
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


void Levelinit(Level *lvl, float tileSize){
    for (int i = 0; i < lvl->platformCount; i++) {
        Platform *p = &lvl->platforms[i];
        
        p->rect = (Rectangle){ // Calcul de la position et taille réelle par rapport a tile_size
            p->x * tileSize,
            p->y * tileSize,
            p->width * tileSize,
            p->high * tileSize
        };
    

    p->color = p->solid ? DARKGRAY : GRAY; // TEMPORAIRE POUR TEST LES DIFFERENT TYPES
    if (strcmp(p->type, "BASIC_PLATFORM_S") == 0) p->color = DARKBLUE; // TEMPORAIRE POUR TEST LES DIFFERENT TYPES
    }
}

void Leveldraw(Level *lvl) {
    for (int i = 0; i < lvl->platformCount; i++) {
        DrawRectangleRec(lvl->platforms[i].rect, lvl->platforms[i].color);
    }
}

#define Reflargeur 1920
#define Refhauteur 1080

int main(){
    if (!readJsonLvl("map1")) return -1;

    SetConfigFlags(FLAG_FULLSCREEN_MODE);

    InitWindow(0, 0, "TEST MAP");
    SetTargetFPS(60);   

    float dynamicTileSize = (float)GetScreenHeight() / Refhauteur; // Taille dynamique en fonction de la taille de la fenêtre

    Levelinit(&currentLevel, dynamicTileSize);

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    while (!WindowShouldClose()){
        float cameraSpeed = 800.0f * GetFrameTime(); 
        
        if (IsKeyDown(KEY_UP)) camera.target.y -= cameraSpeed;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += cameraSpeed;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        Leveldraw(&currentLevel);

        EndMode2D();

        EndDrawing();
    }

    return 0;
}


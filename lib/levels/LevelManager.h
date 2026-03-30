#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "Platform.h"
#include "../../lib/cJson/cJSON.h"


#define MAX_PLATFORMS 100
#define MAX_ENEMIES 50
#define MAX_HAZARDS 50
#define MAX_TRIGGERS 20


// Structures du contenu de la Map
typedef struct {
    char id[32];
    char title[64];
    int width;
    int height;
} MapInfo;

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

int readJsonLvl(const char * fileName);
void LevelInit(float tileSize);
void LevelDraw(void);

extern Level currentLevel; // Déclaration du niveau

#endif

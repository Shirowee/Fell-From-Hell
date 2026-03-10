#include "../raylib/include/raylib.h"
#include "../lib/cJson/cJSON.h"
#include "stdio.h"


int main(){

    InitWindow(1600, 900, "TEST MAP");
    SetTargetFPS(60);

    while (!WindowShouldClose()){

    }

    return 0;
}


void readJsonLvl(const char * fileName){
    const char path = TextFormat("../lib/%s.json",fileName); // Création du chemin complet jusqu'à la map choisi 

    FILE * f = fopen(path,"r");
    if(f == NULL) {printf("Impossible d'ouvrir le fichier"); return 0;}

    // Lecture du fichier JSON
    char buffer[2048];
    int jsonMap = fread(buffer, 1, sizeof(buffer), f);
    fclose(f);

    cJSON *json = cJSON_Parse(buffer);
    if(json == NULL){
        const char *errorPtr = cJSON_GetErrorPtr();
        if (errorPtr != NULL) { // Aide pour débuguer le JSON s'il y a une erreur
            printf("Erreur: %s\n", errorPtr);
        }
        cJSON_Delete(json);
        return 1;
    }
    
    cJSON *map_info = cJSON_GetObjectItemCaseSensitive(json, "map_info");
    printf("Map:%s\n", map_info->valuestring);
}



#include "../raylib/include/raylib.h"
#include "../lib/cJson/cJSON.h"
#include <stdio.h>
#include <stdlib.h>

void displayExtractData(cJSON *json) {
    if (json == NULL) {
        printf("Erreur : Aucun objet JSON à afficher.\n");
        return;
    }

    // cJSON_Print crée une chaîne de caractères formatée (avec retours à la ligne et espaces)
    char *jsonRawString = cJSON_Print(json); 

    if (jsonRawString != NULL) {
        printf("=== DONNÉES EXTRAITES DU JSON ===\n");
        printf("%s\n", jsonRawString);
        printf("==================================\n");

        // TRÈS IMPORTANT : cJSON_Print alloue de la mémoire, il faut la libérer après usage
        free(jsonRawString); 
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

    displayExtractData(json);

    cJSON_Delete(json);

    
    
    /*cJSON *map_info = cJSON_GetObjectItemCaseSensitive(json, "map_info");
    printf("Map:%s\n", map_info->valuestring);*/
    return 1;
}


int main(){

    readJsonLvl("map1");

    /*InitWindow(1600, 900, "TEST MAP");
    SetTargetFPS(60);

    while (!WindowShouldClose()){

    }*/

    return 0;
}


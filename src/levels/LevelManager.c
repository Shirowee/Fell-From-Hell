#include "../../lib/levels/LevelManager.h"
#include "../../lib/levels/Platform.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/cJson/cJSON.h"
#include "stdio.h"

// Sol unique du niveau
static Platform ground;
static Platform platfrom;

void readJsonLvl(const char * fileName){
    const char path = TextFormat("../../lib/%s.json",fileName); // Création du chemin complet jusqu'à la map choisi 

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
    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
}

//init le sol
void LevelInit(void)
{
    ground.rect = (Rectangle){ 0, 400, 800, 50 };
        
}


//dessine le sol
void LevelDraw(void)
{
    DrawRectangleRec(ground.rect, DARKGRAY);
}

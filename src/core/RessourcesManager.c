/**
 * @file RessourcesManager.c
 * @brief Gestion des ressources du jeu
 * 
 * Définit l’interface de gestion des ressources du jeu, y compris
 * les textures, sons et autres éléments graphiques.
 *
 * Fournit des fonctions pour :
 * - charger les ressources
 * - libérer les ressources
 * - accéder aux ressources
 *
 * @author A. Pocholle
 */

#include "../../raylib/include/raylib.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_TEXTURES 128

typedef struct {
    char path[256];
    Texture2D texture;
    bool loaded;
} TextureResource;

static TextureResource textures[MAX_TEXTURES];
static int textureCount = 0;


static int FindTexture(const char *path)
{
    for (int i = 0; i < textureCount; i++)
    {
        if (strcmp(textures[i].path, path) == 0)
        {
            return i;
        }
    }
    return -1;
}

Texture2D* RM_GetTexture(const char *path)
{
    int index = FindTexture(path);

    if (index != -1)
    {
        return &textures[index].texture;
    }

    if (textureCount >= MAX_TEXTURES)
    {
        printf("ERROR: Max textures reached!\n");
        return NULL;
    }


    Texture2D tex = LoadTexture(path);

    textures[textureCount].texture = tex;
    strncpy(textures[textureCount].path, path, 255);
    textures[textureCount].path[255] = '\0';
    textures[textureCount].loaded = true;

    textureCount++;

    return &textures[textureCount - 1].texture;
}

void LoadGameResources()
{
    RM_GetTexture("../ressources/sprites/player/player.png");
    RM_GetTexture("../ressources/sprites/bgs/Nebula.png");
    RM_GetTexture("../ressources/sprites/others/Title.png");
}


void RM_UnloadTexture(const char *path)
{
    int index = FindTexture(path);

    if (index == -1) return;

    UnloadTexture(textures[index].texture);

    // Décaler le tableau
    for (int i = index; i < textureCount - 1; i++)
    {
        textures[i] = textures[i + 1];
    }

    textureCount--;
}


void RM_UnloadAll(void)
{
    for (int i = 0; i < textureCount; i++)
    {
        if (textures[i].loaded)
        {
            UnloadTexture(textures[i].texture);
        }
    }

    textureCount = 0;
}

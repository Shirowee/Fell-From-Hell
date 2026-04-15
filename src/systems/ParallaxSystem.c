/**
 * @file Parallax.c
 * @brief Implémentation du système de parallax scrolling
 * @author A. Pocholle
 */
#include "../../lib/systems/ParallaxSystem.h"

#include "../../lib/core/ResolutionManager.h"
#include "../../lib/core/RessourcesManager.h"
#include <math.h>
#include <stdio.h>

void ParallaxInit(ParallaxSystem *ps)
{
    ps->layerCount = 0;
}

/*--------------------------------------------------*/

void ParallaxAddLayer(ParallaxSystem *ps, Texture2D texture, float speed)
{
    if (ps->layerCount >= PARALLAX_MAX_LAYERS)
    {
        printf("[Parallax] Max layers reached!\n");
        return;
    }
    printf("tex id loaded: %d\n", texture.id);

    ps->layers[ps->layerCount].texture = texture;
    ps->layers[ps->layerCount].speed = speed;
    ps->layers[ps->layerCount].offset = (Vector2){0, -100.0f};

    ps->layerCount++;
}

/*--------------------------------------------------*/

void ParallaxDraw(ParallaxSystem *ps, Camera2D camera, Player *player)
{
    for (int i = 0; i < ps->layerCount; i++)
    {
        ParallaxLayer *l = &ps->layers[i];

        float texW = (float)l->texture.width;
        float texH = (float)l->texture.height;

        Vector2 camTopLeft = GetScreenToWorld2D((Vector2){0, 0}, camera);

        float camX = camTopLeft.x * l->speed;
        float camY = camTopLeft.y * l->speed;

        camX += l->offset.x;
        camY += l->offset.y;

        float x = -fmodf(camX, texW);
        float y = -fmodf(camY, texH);

        if (x > 0) x -= texW;
        if (y > 0) y -= texH;

        for (float drawX = x; drawX < GetScreenWidth() + texW; drawX += texW)
        {
            for (float drawY = y; drawY < GetScreenHeight() + texH; drawY += texH)
            {
                DrawTextureEx(
                    l->texture,
                    (Vector2){drawX, drawY},
                    0.0f,
                    1.0f,
                    WHITE
                );
            }
        }
    }
}
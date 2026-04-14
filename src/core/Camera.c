#include "../../lib/core/ResolutionManager.h"
#include "../../raylib/include/raylib.h"
#include "../../lib/core/WindowManager.h"
#include "../../lib/player/Player.h"
#include "../../lib/levels/LevelManager.h"
#include <stdio.h>

void CameraUpdate(Camera2D *camera, Player *player){

    camera->target.y = player->position.y + player->size.y - resolution.screenH*0.5f;

    if (camera->target.y < 0.0f) {
        camera->target.y = 0.0f;
    }

    if (camera->target.y > (float)currentLevel.info.height ) {
        camera->target.y = (float)currentLevel.info.height;
    }
}
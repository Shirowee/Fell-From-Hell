/**
 * \file Camera.h
 * \author Thomas
 * \brief Ce fichier Camera.h sert a la gestion de tout ce qui concerne la caméra
 */

#ifndef TRIGGER_SYSTEM_H
#define TRIGGER_SYSTEM_H

#include "../player/Player.h"
#include "../../raylib/include/raylib.h"

void CameraUpdate(Camera2D *camera, Player *player);

#endif
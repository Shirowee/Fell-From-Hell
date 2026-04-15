#include "../../lib/core/SavingManager.h"
#include "../../lib/levels/LevelManager.h"
#include "../../lib/systems/EnemySpawner.h"
#include "../../raylib/include/raylib.h"
#include <string.h>

#define SAVE_FILE "Save.dat"

void SaveGame(Player *player)
{
    SaveInfo info;

    strncpy(info.mapId, currentLevel.info.id, sizeof(info.mapId));
    info.mapId[sizeof(info.mapId) - 1] = '\0';

    info.weapon          = player->weapon;
    info.buff            = *(player->buff);
    info.difficultyMultHP  = enemySpawner.difficultyMultHP;
    info.difficultyMultDMG = enemySpawner.difficultyMultDMG;

    SaveFileData(SAVE_FILE, &info, sizeof(SaveInfo));
}

bool LoadGame(Player *player)
{
    int size = 0;
    unsigned char *file = LoadFileData(SAVE_FILE, &size);

    if (file == NULL || size != (int)sizeof(SaveInfo)) {
        if (file) UnloadFileData(file);
        return false;
    }

    SaveInfo info;
    memcpy(&info, file, sizeof(SaveInfo));
    UnloadFileData(file);

    if (!readJsonLvl(info.mapId)) return false;
    LevelInit();

    player->weapon = info.weapon;
    *(player->buff) = info.buff;
    enemySpawner.difficultyMultHP  = info.difficultyMultHP;
    enemySpawner.difficultyMultDMG = info.difficultyMultDMG;

    return true;
}

bool HasSaveFile(void)
{
    return FileExists(SAVE_FILE);
}

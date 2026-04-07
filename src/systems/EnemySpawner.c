/**
 * @file EnemySpawner.c
 * @brief Gestion de l'apparition dynamique des ennemis
 * @author A. Pocholle
 * 
 * Responsable du spawn automatique des ennemis
 * à intervalles réguliers.
 * 
 * Le système fonctionne avec :
 * - un timer interne
 * - un cooldown variable
 * - un spawn aléatoire sur l'écran
 */

#include "../../raylib/include/raylib.h"
#include "../../lib/systems/EnemySpawner.h"

EnemySpawner enemySpawner;

void EnemySpawnerInit(EnemySpawner* spawner)
{
    spawner->timer = 0;
    spawner->cooldown = 0.5f;
}

void SpawnRandomEnemy(enemyPool_t* bulletPool){
    SpawnEnemyPool(bulletPool, 
        (Vector2){GetRandomValue(0, GetScreenWidth()), 
            GetRandomValue(0, GetScreenHeight())}, 
            GetRandomValue(50, 150), 
            (Vector2){GetRandomValue(30, 150), GetRandomValue(30, 150)}, 
            GetRandomValue(5, 15), 
            GetRandomValue(100, 150), 
            GetRandomValue(20, 30));
}

void UpdateEnemySpawner(EnemySpawner* spawner, enemyPool_t* pool)
{
    float dt = GetFrameTime();

    spawner->timer += dt;

    if (spawner->timer >= spawner->cooldown)
    {
        SpawnRandomEnemy(pool);

        spawner->timer = 0;
        spawner->cooldown = GetRandomValue(3, 5);
    }
}
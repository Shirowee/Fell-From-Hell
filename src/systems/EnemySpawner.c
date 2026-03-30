#include "../../raylib/include/raylib.h"
#include "../../lib/systems/EnemySpawner.h"

EnemySpawner enemySpawner;

void EnemySpawnerInit(EnemySpawner* spawner)
{
    spawner->timer = 0;
    spawner->cooldown = 2.0f;
}

void SpawnRandomEnemy(enemyPool_t* bulletPool){
    SpawnEnemyPool(bulletPool, 
        (Vector2){GetRandomValue(0, GetScreenWidth()), GetRandomValue(0, GetScreenHeight())}, 
                    GetRandomValue(50, 150), (Vector2){GetRandomValue(30, 150), GetRandomValue(30, 150)}, 
                    GetRandomValue(5, 15), GetRandomValue(300, 600), GetRandomValue(20, 30));
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
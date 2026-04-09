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
            GetRandomValue(20, 30),
            GetRandomValue(0, 4)
    );

}

void UpdateEnemySpawner(EnemySpawner* spawner, enemyPool_t* pool)
{
    float dt = GetFrameTime();

    spawner->timer += dt;

    if (spawner->timer >= spawner->cooldown)
    {
        SpawnEnemyPatternCircle(spawner, pool, (Vector2){GetRandomValue(0, GetScreenWidth()), GetRandomValue(0, GetScreenHeight())});

        spawner->timer = 0;
        spawner->cooldown = GetRandomValue(3, 5);
    }
}

void SpawnEnemyPatternChasers(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos)
{
    //chasers
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 100, pos.y + 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 100, pos.y + 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 150, pos.y - 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 150, pos.y - 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x, pos.y-180}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);

}

void SpawnEnemyPatternCircle(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos)
{
    //chasers
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 100, pos.y + 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 100, pos.y + 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 150, pos.y - 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 150, pos.y - 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x, pos.y-180}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    //circle
    SpawnEnemyPool(pool, 
        (Vector2)pos, 
        150, 
        (Vector2){75,75}, 
        20, 
        150, 
        20,
        ENEMY_SHOOTER_CIRCLE);   

}

void SpawnEnemyPatternShooter(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos)
{
    //chasers
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 100, pos.y + 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 100, pos.y + 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 150, pos.y - 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 150, pos.y - 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x, pos.y-180}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    //s
    SpawnEnemyPool(pool, 
        (Vector2)pos, 
        150, 
        (Vector2){75,75}, 
        20, 
        150, 
        20,
        ENEMY_SHOOTER);   
}

void SpawnEnemyPatternArc(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos)
{
    //chasers
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 150, pos.y - 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 150, pos.y - 100}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x, pos.y-180}, 
        200, 
        (Vector2){50,50}, 
        10, 
        100, 
        20,
        0);
    //arc
    SpawnEnemyPool(pool, 
        (Vector2)pos, 
        150, 
        (Vector2){75,75}, 
        20, 
        150, 
        20,
        ENEMY_ARC);   

}
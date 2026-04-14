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
#include "../../lib/levels/LevelManager.h"
#include <stdio.h>


EnemySpawner enemySpawner;


void EnemySpawnerInit(EnemySpawner* spawner)
{
    spawner->nbVague = 0;
    spawner->timer = 0;
    spawner->cooldown = 0.5f;
    spawner->difficultyMultHP =1.0f;
    spawner->difficultyMultDMG =1.0f;
}

void SpawnRandomEnemy(enemyPool_t* bulletPool){
    SpawnEnemyPool(bulletPool, 
        (Vector2){GetRandomValue(0, GetScreenWidth()), 
            GetRandomValue(0, GetScreenHeight())}, 
            GetRandomValue(50, 150),
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


    if (spawner->timer >= currentLevel.enemies[spawner->nbVague].spawnTime)
    {
        
        switch (currentLevel.enemies[spawner->nbVague].nbType)
        {
        case 1 :
        if (currentLevel.enemies[spawner->nbVague].spawned == false ){
            SpawnEnemyPatternChasers(spawner, pool, (Vector2){currentLevel.enemies[spawner->nbVague].position.x, currentLevel.enemies[spawner->nbVague].position.y});
            currentLevel.enemies[spawner->nbVague].spawned = true;
            spawner->nbVague++;
            spawner->timer=0;
        }
        break;
            
        case 2 :
        if (currentLevel.enemies[spawner->nbVague].spawned == false ){
            SpawnEnemyPatternShooter(spawner, pool, (Vector2){currentLevel.enemies[spawner->nbVague].position.x, currentLevel.enemies[spawner->nbVague].position.y});
            currentLevel.enemies[spawner->nbVague].spawned = true;
            spawner->nbVague++;
            spawner->timer=0;
        }
            break;
        case 3 :
        if (currentLevel.enemies[spawner->nbVague].spawned == false ){
            SpawnEnemyPatternCircle(spawner, pool, (Vector2){currentLevel.enemies[spawner->nbVague].position.x, currentLevel.enemies[spawner->nbVague].position.y});
            currentLevel.enemies[spawner->nbVague].spawned = true;
            spawner->nbVague++;
            spawner->timer=0;
        }
            break;
        case 4 :
        if (currentLevel.enemies[spawner->nbVague].spawned == false ){
            SpawnEnemyPatternSpiral(spawner, pool, (Vector2){currentLevel.enemies[spawner->nbVague].position.x, currentLevel.enemies[spawner->nbVague].position.y});
            currentLevel.enemies[spawner->nbVague].spawned = true;
            spawner->nbVague++;
            spawner->timer=0;
        }
            break;
        case 5 :
        if (currentLevel.enemies[spawner->nbVague].spawned == false ){
            SpawnEnemyPatternArc(spawner, pool, (Vector2){currentLevel.enemies[spawner->nbVague].position.x, currentLevel.enemies[spawner->nbVague].position.y});
            currentLevel.enemies[spawner->nbVague].spawned = true;
            spawner->nbVague++;
            spawner->timer=0;
        }
            break;
        
        default:
            break;
        }
    }
}

void SpawnEnemyPatternChasers(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos)
{
    //chasers
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 100, pos.y + 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 100, pos.y + 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x, pos.y-180}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);

}

void SpawnEnemyPatternCircle(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos)
{
    //chasers
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 100, pos.y + 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 100, pos.y + 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x, pos.y-180}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    //circle
    SpawnEnemyPool(pool, 
        (Vector2)pos, 
        SHOOTER_HP*spawner->difficultyMultHP,
        150, 
        (Vector2){75,75}, 
        SHOOTER_DMG*spawner->difficultyMultDMG, 
        150, 
        20,
        ENEMY_SHOOTER_CIRCLE);   

}

void SpawnEnemyPatternShooter(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos)
{
    //chasers
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 100, pos.y + 100},
        CHASER_HP*spawner->difficultyMultHP, 
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 100, pos.y + 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x, pos.y-180}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    //s
    SpawnEnemyPool(pool, 
        (Vector2)pos, 
        SHOOTER_HP*spawner->difficultyMultHP,
        150, 
        (Vector2){75,75}, 
        SHOOTER_DMG*spawner->difficultyMultDMG, 
        150, 
        20,
        ENEMY_SHOOTER);   
}

void SpawnEnemyPatternArc(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos)
{
    //chasers
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x, pos.y-180}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    //arc
    SpawnEnemyPool(pool, 
        (Vector2)pos, 
        SHOOTER_HP*spawner->difficultyMultHP,
        150, 
        (Vector2){75,75}, 
        SHOOTER_DMG*spawner->difficultyMultDMG, 
        150, 
        20,
        ENEMY_ARC);   

}

void SpawnEnemyPatternSpiral(EnemySpawner* spawner, enemyPool_t* pool, Vector2 pos)
{
    //chasers
    SpawnEnemyPool(pool, 
        (Vector2){pos.x - 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x + 150, pos.y - 100}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    SpawnEnemyPool(pool, 
        (Vector2){pos.x, pos.y-180}, 
        CHASER_HP*spawner->difficultyMultHP,
        200, 
        (Vector2){50,50}, 
        CHASER_DMG*spawner->difficultyMultDMG, 
        100, 
        20,
        0);
    //spiral
    SpawnEnemyPool(pool, 
        (Vector2)pos, 
        SHOOTER_HP*spawner->difficultyMultHP,
        150, 
        (Vector2){75,75}, 
        SHOOTER_DMG*spawner->difficultyMultDMG, 
        150, 
        20,
        ENEMY_SPIRAL);   

}
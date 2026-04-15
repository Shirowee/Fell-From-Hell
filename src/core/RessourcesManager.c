/**
 * @file RessourcesManager.h
 * @brief Gestion des ressources du jeu (textures et sons)
 *
 * Fournit un système centralisé pour charger, stocker et libérer
 * les ressources du jeu (textures et effets sonores).
 *
 * Les ressources sont identifiées par leur chemin (path).
 *
 * Fonctionnalités :
 * - Chargement automatique (lazy loading)
 * - Mise en cache (évite les doublons)
 * - Déchargement individuel ou global
 * - Gestion du volume global des effets sonores
 *
 * @author A. Pocholle
 */


#include "../../lib/core/RessourcesManager.h"
#include <stdbool.h>
#include <stdio.h>


#define MUSIC_NONE MUSIC_COUNT

static MusicID currentMusic = MUSIC_NONE;

/* =========================
   TEXTURES
   ========================= */

static Texture2D textures[TEX_COUNT];
static bool texturesLoaded[TEX_COUNT] = {0};

static const char* texturePaths[TEX_COUNT] = {
    "../ressources/sprites/player/player.png", // TEX_PLAYER
    "../ressources/sprites/bgs/Nebula.png", // TEX_BACKGROUND_NEBULA
    "../ressources/sprites/others/Title.png", // TEX_TITLE
    "../ressources/sprites/others/tileset.png", // TEX_TILESET
    "../ressources/sprites/enemies/chaser.png", // TEX_CHASER
    "../ressources/sprites/enemies/shooter.png", // TEX_SHOOTER
    "../ressources/sprites/enemies/huit.png", // TEX_HUIT
    "../ressources/sprites/enemies/spiral.png", // TEX_SPIRAL
    "../ressources/sprites/enemies/arc.png", // TEX_ARC
    "../ressources/sprites/bgs/parallax_neb/bg.png", // TEX_PARALLAX_NEB_BG
    "../ressources/sprites/bgs/parallax_neb/1.png", // TEX_PARALLAX_NEB_1
    "../ressources/sprites/bgs/parallax_neb/3.png", // TEX_PARALLAX_NEB_3
    "../ressources/sprites/bgs/parallax_neb/4.png", // TEX_PARALLAX_NEB_4
    "../ressources/sprites/bgs/parallax_neb/5.png" // TEX_PARALLAX_NEB_5
};

Texture2D* RM_GetTexture(TextureID id)
{
    if (!texturesLoaded[id])
    {
        textures[id] = LoadTexture(texturePaths[id]);
        texturesLoaded[id] = true;
    }

    return &textures[id];
}

/* =========================
   MUSIQUE
   ========================= */

static Music music[MUSIC_COUNT];
static bool musicLoaded[MUSIC_COUNT] = {0};

static float globalMusicVolume = 1.0f;

static const char* musicPaths[MUSIC_COUNT] = {
    "../ressources/music/menu.ogg",
    "../ressources/music/level1.ogg",
};

Music* RM_GetMusic(MusicID id)
{
    if (!musicLoaded[id])
    {
        music[id] = LoadMusicStream(musicPaths[id]);
        SetMusicVolume(music[id], globalMusicVolume);
        musicLoaded[id] = true;
    }

    return &music[id];
}

void RM_PlayMusic(MusicID id)
{
    if (currentMusic != MUSIC_COUNT)
    {
        StopMusicStream(music[currentMusic]);
    }

    Music* m = RM_GetMusic(id);

    PlayMusicStream(*m);
    SetMusicVolume(*m, globalMusicVolume);

    currentMusic = id;
}

void RM_UpdateMusic(void)
{
    if (currentMusic != MUSIC_COUNT)
    {
        UpdateMusicStream(music[currentMusic]);
    }
}

void RM_StopMusic(void)
{
    if (currentMusic != MUSIC_COUNT)
    {
        StopMusicStream(music[currentMusic]);
        currentMusic = MUSIC_COUNT;
    }
}

void RM_SetMusicVolume(float volume)
{
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 1.0f) volume = 1.0f;

    globalMusicVolume = volume;

    for (int i = 0; i < MUSIC_COUNT; i++)
    {
        if (musicLoaded[i])
        {
            SetMusicVolume(music[i], volume);
        }
    }
}

/* =========================
   SOUNDS
   ========================= */

static Sound sounds[SND_COUNT];
static bool soundsLoaded[SND_COUNT] = {0};
static float globalSFXVolume = 1.0f; // [0.0 - 1.0]

static const char* soundPaths[SND_COUNT] = {
    "../ressources/sfx/dash.wav", // SND_DASH
    "../ressources/sfx/enemyDie.wav", // SND_ENEMY_DIE
    "../ressources/sfx/enemyHurt.wav", // SND_ENEMY_HURT
    "../ressources/sfx/enemyShoot.wav", // SND_ENEMY_SHOOT
    "../ressources/sfx/hurt.wav", // SND_HURT
    "../ressources/sfx/jump.wav", // SND_JUMP
    "../ressources/sfx/shoot.wav", // SND_SHOOT
    "../ressources/sfx/select.wav", // SND_SELECT
    "../ressources/sfx/selected.wav" // SND_SELECTED
};

Sound* RM_GetSound(SoundID id)
{
    if (!soundsLoaded[id])
    {
        sounds[id] = LoadSound(soundPaths[id]);
        SetSoundVolume(sounds[id], globalSFXVolume); // appliquer volume
        soundsLoaded[id] = true;
    }

    return &sounds[id];
}

/* wrapper */
void RM_PlaySound(SoundID id)
{
    Sound* s = RM_GetSound(id);

    // sécurité : toujours appliquer le volume actuel
    SetSoundVolume(*s, globalSFXVolume);

    PlaySound(*s);
}

/* =========================
   VOLUME GLOBAL
   ========================= */


float RM_GetSFXVolume(void)
{
    return globalSFXVolume;
}

void RM_SetSFXVolume(float volume)
{
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 1.0f) volume = 1.0f;

    globalSFXVolume = volume;

    // appliquer aux sons déjà chargés
    for (int i = 0; i < SND_COUNT; i++)
    {
        if (soundsLoaded[i])
        {
            SetSoundVolume(sounds[i], globalSFXVolume);
        }
    }
}




/* =========================
   LOAD / UNLOAD
   ========================= */

void RM_LoadAll(void)
{
    // textures
    for (int i = 0; i < TEX_COUNT; i++)
    {
        textures[i] = LoadTexture(texturePaths[i]);
        texturesLoaded[i] = true;
    }

    // sounds
    for (int i = 0; i < SND_COUNT; i++)
    {
        sounds[i] = LoadSound(soundPaths[i]);
        SetSoundVolume(sounds[i], globalSFXVolume);
        soundsLoaded[i] = true;
    }
}

void RM_UnloadAll(void)
{
    // textures
    for (int i = 0; i < TEX_COUNT; i++)
    {
        if (texturesLoaded[i])
        {
            UnloadTexture(textures[i]);
        }
    }

    // sounds
    for (int i = 0; i < SND_COUNT; i++)
    {
        if (soundsLoaded[i])
        {
            UnloadSound(sounds[i]);
        }
    }

    // musiques
    for (int i = 0; i < MUSIC_COUNT; i++)
    {
        if (musicLoaded[i])
        {
            UnloadMusicStream(music[i]);
        }
    }
}
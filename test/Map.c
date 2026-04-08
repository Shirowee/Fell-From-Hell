#include "../raylib/include/raylib.h"
#include "../lib/core/WindowManager.h"
#include "../lib/core/ResolutionManager.h"
#include "../lib/levels/LevelManager.h"
#include "../lib/player/PlayerController.h"
#include "../lib/player/PlayerMovement.h"
#include "../lib/systems/BulletPool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAP_NAME "map1"
#define MAP_PATH "../lib/map/map1.json"
#define MAX_EDITOR_SELECT 2048
#define MAX_UNDO 1000

// --- SYSTÈME D'UNDO / REDO ---
Level *undoStack = NULL;
int undoPtr = 0;
int maxUndo = 0;

typedef enum { MODE_EDITOR, MODE_TEST } EditorMode;

// Presse-papier pour le Copier-Coller
Platform clipboard[MAX_EDITOR_SELECT];
int clipboardCount = 0;
Vector2 clipboardOffset[MAX_EDITOR_SELECT];

bool IsLevelDifferent(Level *a, Level *b) {
    if (a->info.height != b->info.height || a->platformCount != b->platformCount) return true;
    if (a->playerStart.x != b->playerStart.x || a->playerStart.y != b->playerStart.y) return true;
    for (int i = 0; i < a->platformCount; i++) {
        if (a->platforms[i].x != b->platforms[i].x || a->platforms[i].y != b->platforms[i].y ||
            a->platforms[i].width != b->platforms[i].width || a->platforms[i].high != b->platforms[i].high ||
            a->platforms[i].solid != b->platforms[i].solid) return true;
    }
    return false;
}

void CommitCurrentState() {
    if (!undoStack) return;
    if (IsLevelDifferent(&undoStack[undoPtr], &currentLevel)) {
        undoPtr++;
        if (undoPtr >= MAX_UNDO) {
            memmove(undoStack, undoStack + 1, (MAX_UNDO - 1) * sizeof(Level));
            undoPtr = MAX_UNDO - 1;
        }
        undoStack[undoPtr] = currentLevel;
        maxUndo = undoPtr;
    }
}

void Undo() {
    if (undoPtr > 0 && undoStack != NULL) { 
        undoPtr--; 
        currentLevel = undoStack[undoPtr]; 
    }
}

void Redo() {
    if (undoPtr < maxUndo && undoStack != NULL) { 
        undoPtr++; 
        currentLevel = undoStack[undoPtr]; 
    }
}

// --- UTILITAIRES ---
float Snap(float value, int gridSize) { return round(value / gridSize) * gridSize; }
int SnapHeight(int height, int tileSize) { return (int)ceil((float)height / tileSize) * tileSize; }

void ShiftMap(float deltaY) {
    for (int i = 0; i < currentLevel.platformCount; i++) {
        currentLevel.platforms[i].y += deltaY; 
        currentLevel.platforms[i].rect.y += deltaY;
    }
    currentLevel.playerStart.y += (int)deltaY;
    for (int i = 0; i < currentLevel.hazardCount; i++) {
        currentLevel.hazards[i].position.y += (int)deltaY;
    }
}

Rectangle GetLasso(Vector2 p1, Vector2 p2) {
    return (Rectangle){ fminf(p1.x, p2.x), fminf(p1.y, p2.y), fabsf(p1.x - p2.x), fabsf(p1.y - p2.y) };
}

// --- SAUVEGARDE JSON ---
void SaveLevelToJson(const char* fileName) {
    currentLevel.info.height = SnapHeight(currentLevel.info.height, 64);
    FILE *file = fopen(fileName, "w");
    if (!file) return;

    fprintf(file, "{\n");
    fprintf(file, "  \"map_info\": {\n");
    fprintf(file, "    \"id\": \"%s\", \"title\": \"%s\",\n", currentLevel.info.id, currentLevel.info.title);
    fprintf(file, "    \"dimensions\": { \"w\": %d, \"h\": %d }\n", currentLevel.info.width, currentLevel.info.height);
    fprintf(file, "  },\n");

    fprintf(file, "  \"platforms\": [\n");
    for (int i = 0; i < currentLevel.platformCount; i++) {
        Platform *p = &currentLevel.platforms[i];
        fprintf(file, "    { \"type\": \"%s\", \"solid\": %d, \"x\": %.0f, \"y\": %.0f, \"width\": %.0f, \"high\": %.0f }",
                p->type, p->solid, p->x, p->y, p->width, p->high);
        if (i < currentLevel.platformCount - 1) fprintf(file, ",");
        fprintf(file, "\n");
    }
    fprintf(file, "  ],\n");

    fprintf(file, "  \"entities\": {\n");
    fprintf(file, "    \"player_start\": { \"x\": %d, \"y\": %d },\n", (int)currentLevel.playerStart.x, (int)currentLevel.playerStart.y);
    fprintf(file, "    \"enemies\": [],\n"); 
    
    fprintf(file, "    \"hazards\": [\n");
    for (int i = 0; i < currentLevel.hazardCount; i++) {
        fprintf(file, "      { \"type\": \"%s\", \"x\": %d, \"y\": %d }", currentLevel.hazards[i].type, (int)currentLevel.hazards[i].position.x, (int)currentLevel.hazards[i].position.y);
        if (i < currentLevel.hazardCount - 1) fprintf(file, ",");
        fprintf(file, "\n");
    }
    fprintf(file, "    ]\n  },\n");
    fprintf(file, "  \"triggers\": []\n}\n");
    fclose(file);
}

int main(void) {
    ChangeDirectory(GetApplicationDirectory());
    if (!readJsonLvl(MAP_NAME)) return -1;
    
    undoStack = (Level*)malloc(MAX_UNDO * sizeof(Level));
    currentLevel.info.width = 2048; 
    currentLevel.info.height = SnapHeight(currentLevel.info.height, 64);

    WindowInit();
    ResolutionInit(currentLevel.info.width, currentLevel.info.height);
    LevelInit();
    
    undoStack[0] = currentLevel;

    Player testPlayer;
    PlayerInit(&testPlayer);
    InitBulletPool(&playerBulletPool, 500); 
    double timeSpent = 0, startReload = 0;

    EditorMode mode = MODE_EDITOR;
    Vector2 editorCameraTarget = { 1024, currentLevel.info.height / 2.0f };
    int tileSize = 64; 
    char message[64] = "";
    int messageTimer = 0;
    
    bool isSelected[MAX_EDITOR_SELECT] = {0};
    bool isSpawnSelected = false; 
    float initialX[MAX_EDITOR_SELECT], initialY[MAX_EDITOR_SELECT], initialSpawnX, initialSpawnY;
    bool isDragging = false, isLassoing = false;
    Vector2 dragStartMouse, lassoStart;
    
    // Nouveaux variables pour la création par grille
    bool isGridCreating = false;
    Vector2 gridCreateStart = {0};

    double lastClickTime = 0;
    int lastClickedIndex = -2;
    float mapResizeTimer = 0.0f, platResizeTimer = 0.0f;
    const float repeatInterval = 0.12f;

    Camera2D camera = { 0 };
    camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.target = editorCameraTarget;
    camera.zoom   = resolution.scale;

    while (!WindowShouldClose()) {
        WindowManager_Update();
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
        float dt = GetFrameTime();

        // --- BASCULE MODE TEST / EDITEUR (T) ---
        if (IsKeyPressed(KEY_T)) {
            if (mode == MODE_EDITOR) {
                mode = MODE_TEST; 
                editorCameraTarget = camera.target;
                PlayerInit(&testPlayer);
                testPlayer.position = (Vector2){ (float)currentLevel.playerStart.x, (float)currentLevel.playerStart.y };
                for(int i = 0; i < playerBulletPool.capacity; i++) playerBulletPool.tab[i].active = 0;
            } else { 
                mode = MODE_EDITOR; 
                camera.target = editorCameraTarget; 
            }
        }

        if (mode == MODE_EDITOR) {
            
            // --- UNDO / REDO --- 
            if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_W))) { 
                Undo(); 
                for (int i = 0; i < MAX_EDITOR_SELECT; i++) isSelected[i] = false; 
                isSpawnSelected = false; 
                strcpy(message, "UNDO"); messageTimer = 40; 
            }
            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Y)) { 
                Redo(); 
                for (int i = 0; i < MAX_EDITOR_SELECT; i++) isSelected[i] = false; 
                isSpawnSelected = false; 
                strcpy(message, "REDO"); messageTimer = 40; 
            }

            // --- COPIER (CTRL+C) ---
            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C) && !isGridCreating) {
                clipboardCount = 0;
                Vector2 center = {0, 0};
                int count = 0;
                for (int i = 0; i < currentLevel.platformCount; i++) {
                    if (isSelected[i]) {
                        clipboard[clipboardCount] = currentLevel.platforms[i];
                        center.x += currentLevel.platforms[i].x; 
                        center.y += currentLevel.platforms[i].y;
                        clipboardCount++; 
                        count++;
                    }
                }
                if (count > 0) {
                    center.x /= count; 
                    center.y /= count;
                    for (int i = 0; i < clipboardCount; i++) {
                        clipboardOffset[i] = (Vector2){ clipboard[i].x - center.x, clipboard[i].y - center.y };
                    }
                    strcpy(message, "COPIE !"); messageTimer = 60;
                }
            }

            // --- COLLER (CTRL+V) ---
            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V) && !isGridCreating) {
                if (clipboardCount > 0) {
                    for (int i = 0; i < MAX_EDITOR_SELECT; i++) isSelected[i] = false;
                    for (int i = 0; i < clipboardCount; i++) {
                        if (currentLevel.platformCount < MAX_PLATFORMS) {
                            int idx = currentLevel.platformCount;
                            currentLevel.platforms[idx] = clipboard[i];
                            currentLevel.platforms[idx].x = Snap(mouseWorld.x + clipboardOffset[i].x, tileSize);
                            currentLevel.platforms[idx].y = Snap(mouseWorld.y + clipboardOffset[i].y, tileSize);
                            currentLevel.platforms[idx].rect = (Rectangle){currentLevel.platforms[idx].x, currentLevel.platforms[idx].y, currentLevel.platforms[idx].width, currentLevel.platforms[idx].high};
                            isSelected[idx] = true;
                            currentLevel.platformCount++;
                        }
                    }
                    CommitCurrentState();
                    strcpy(message, "COLLE !"); messageTimer = 60;
                }
            }

            // --- TELEPORT SPAWN (P) ---
            if (IsKeyPressed(KEY_P)) {
                currentLevel.playerStart.x = (int)Snap(mouseWorld.x - 15, tileSize);
                currentLevel.playerStart.y = (int)Snap(mouseWorld.y - 25, tileSize);
                CommitCurrentState();
                strcpy(message, "SPAWN PLACE !"); messageTimer = 60;
            }

            // Navigation Camera
            float wheel = GetMouseWheelMove();
            if (wheel != 0) {
                Vector2 m1 = GetScreenToWorld2D(GetMousePosition(), camera);
                camera.zoom += wheel * 0.05f; 
                if (camera.zoom < 0.1f) camera.zoom = 0.1f;
                Vector2 m2 = GetScreenToWorld2D(GetMousePosition(), camera);
                camera.target.x += (m1.x - m2.x); 
                camera.target.y += (m1.y - m2.y);
            }
            if (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_LEFT_CONTROL)) {
                float speed = 900.0f * dt / camera.zoom;
                if (IsKeyDown(KEY_UP)) camera.target.y -= speed; 
                if (IsKeyDown(KEY_DOWN)) camera.target.y += speed;
                if (IsKeyDown(KEY_RIGHT)) camera.target.x += speed; 
                if (IsKeyDown(KEY_LEFT)) camera.target.x -= speed;
            }
            
            // --- CENTRER VUE (H) ---
            if (IsKeyPressed(KEY_H)) {
                camera.target = (Vector2){ currentLevel.info.width / 2.0f, currentLevel.info.height / 2.0f };
                camera.zoom = resolution.scale;
            }

            // Resize Map
            if (IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_Z) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_Y) && !IsKeyDown(KEY_C) && !IsKeyDown(KEY_V) && !IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                mapResizeTimer += dt;
                if (mapResizeTimer >= repeatInterval || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
                    if (IsKeyDown(KEY_UP)) { 
                        currentLevel.info.height += tileSize; 
                        ShiftMap((float)tileSize); 
                        camera.target.y += tileSize; 
                    }
                    if (IsKeyDown(KEY_DOWN) && currentLevel.info.height > tileSize) { 
                        currentLevel.info.height -= tileSize; 
                        ShiftMap(-(float)tileSize); 
                        camera.target.y -= tileSize; 
                    }
                    CommitCurrentState(); 
                    mapResizeTimer = 0;
                }
            } else mapResizeTimer = repeatInterval;

            // --- SÉLECTION, CLICS & CRÉATION GRILLE ---
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                
                // Création de bloc par grille (CTRL + CLIC GAUCHE)
                if (IsKeyDown(KEY_LEFT_CONTROL)) {
                    isGridCreating = true;
                    for (int i = 0; i < MAX_EDITOR_SELECT; i++) isSelected[i] = false;
                    isSpawnSelected = false;
                    gridCreateStart.x = floorf(mouseWorld.x / tileSize) * tileSize;
                    gridCreateStart.y = floorf(mouseWorld.y / tileSize) * tileSize;
                } 
                else {
                    // Comportement standard
                    int clickedIndex = -1; 
                    double currentTime = GetTime();
                    
                    Rectangle spawnRect = { currentLevel.playerStart.x, currentLevel.playerStart.y, 30, 50 };
                    bool clickedSpawn = CheckCollisionPointRec(mouseWorld, spawnRect);
                    
                    if (!clickedSpawn) { 
                        for (int i = currentLevel.platformCount - 1; i >= 0; i--) {
                            if (CheckCollisionPointRec(mouseWorld, (Rectangle){currentLevel.platforms[i].x, currentLevel.platforms[i].y, currentLevel.platforms[i].width, currentLevel.platforms[i].high})) { 
                                clickedIndex = i; 
                                break; 
                            } 
                        } 
                    }

                    if (clickedSpawn) { 
                        isLassoing = false; 
                        if (!isSpawnSelected) { 
                            if (!IsKeyDown(KEY_LEFT_SHIFT)) {
                                for (int i = 0; i < MAX_EDITOR_SELECT; i++) isSelected[i] = false; 
                            }
                            isSpawnSelected = true; 
                        } 
                        isDragging = true; 
                        dragStartMouse = mouseWorld; 
                        initialSpawnX = currentLevel.playerStart.x; 
                        initialSpawnY = currentLevel.playerStart.y; 
                        for (int i = 0; i < currentLevel.platformCount; i++) {
                            if (isSelected[i]) { 
                                initialX[i] = currentLevel.platforms[i].x; 
                                initialY[i] = currentLevel.platforms[i].y; 
                            }
                        }
                    } 
                    else if (clickedIndex != -1) { 
                        isLassoing = false; 
                        
                        if (clickedIndex == lastClickedIndex && (currentTime - lastClickTime) < 0.3) { 
                            bool targetSolid = !currentLevel.platforms[clickedIndex].solid; 
                            for (int i = 0; i < currentLevel.platformCount; i++) {
                                if (isSelected[i]) currentLevel.platforms[i].solid = targetSolid; 
                            }
                            currentLevel.platforms[clickedIndex].solid = targetSolid; 
                            CommitCurrentState(); 
                            lastClickTime = 0; 
                        } else { 
                            lastClickTime = currentTime; 
                            lastClickedIndex = clickedIndex; 
                        } 
                        
                        if (!isSelected[clickedIndex]) { 
                            if (!IsKeyDown(KEY_LEFT_SHIFT)) {
                                for (int i = 0; i < MAX_EDITOR_SELECT; i++) isSelected[i] = false; 
                                isSpawnSelected = false; 
                            }
                            isSelected[clickedIndex] = true; 
                        } 

                        if (IsKeyDown(KEY_LEFT_ALT)) {
                            int originalCount = currentLevel.platformCount;
                            int newlySelected[MAX_EDITOR_SELECT];
                            int newSelectIndex = 0;
                            for (int i = 0; i < originalCount; i++) {
                                if (isSelected[i] && currentLevel.platformCount < MAX_PLATFORMS) {
                                    currentLevel.platforms[currentLevel.platformCount] = currentLevel.platforms[i];
                                    newlySelected[newSelectIndex++] = currentLevel.platformCount;
                                    currentLevel.platformCount++;
                                }
                            }
                            for (int i = 0; i < MAX_EDITOR_SELECT; i++) isSelected[i] = false;
                            for (int j = 0; j < newSelectIndex; j++) isSelected[newlySelected[j]] = true;
                        }

                        isDragging = true; 
                        dragStartMouse = mouseWorld; 
                        for (int i = 0; i < currentLevel.platformCount; i++) {
                            if (isSelected[i]) { 
                                initialX[i] = currentLevel.platforms[i].x; 
                                initialY[i] = currentLevel.platforms[i].y; 
                            } 
                        }
                        if (isSpawnSelected) { 
                            initialSpawnX = currentLevel.playerStart.x; 
                            initialSpawnY = currentLevel.playerStart.y; 
                        } 
                    } 
                    else { 
                        isLassoing = true; 
                        lassoStart = mouseWorld; 
                        if (!IsKeyDown(KEY_LEFT_SHIFT)) { 
                            for (int i = 0; i < MAX_EDITOR_SELECT; i++) isSelected[i] = false; 
                            isSpawnSelected = false; 
                        } 
                        lastClickedIndex = -1;
                    }
                }
            }
            
            // --- RELACHEMENT CLIC GAUCHE ---
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) { 
                if (isGridCreating) {
                    isGridCreating = false;
                    float currentCellX = floorf(mouseWorld.x / tileSize) * tileSize;
                    float currentCellY = floorf(mouseWorld.y / tileSize) * tileSize;
                    float finalX = fminf(gridCreateStart.x, currentCellX);
                    float finalY = fminf(gridCreateStart.y, currentCellY);
                    float finalW = fabsf(currentCellX - gridCreateStart.x) + tileSize;
                    float finalH = fabsf(currentCellY - gridCreateStart.y) + tileSize;

                    if (currentLevel.platformCount < MAX_PLATFORMS) {
                        Level oldState = currentLevel;
                        int i = currentLevel.platformCount;
                        strcpy(currentLevel.platforms[i].type, "BASIC_PLATFORM_S");
                        currentLevel.platforms[i].solid = 1;
                        currentLevel.platforms[i].color = WHITE;
                        currentLevel.platforms[i].x = finalX;
                        currentLevel.platforms[i].y = finalY;
                        currentLevel.platforms[i].width = finalW;
                        currentLevel.platforms[i].high = finalH;
                        currentLevel.platforms[i].rect = (Rectangle){finalX, finalY, finalW, finalH};
                        
                        currentLevel.platformCount++;
                        CommitCurrentState();
                        isSelected[i] = true;
                    }
                }
                
                if (isDragging) { 
                    isDragging = false; 
                    CommitCurrentState(); 
                } 
                if (isLassoing) { 
                    isLassoing = false; 
                    Rectangle l = GetLasso(lassoStart, mouseWorld); 
                    if (CheckCollisionRecs(l, (Rectangle){currentLevel.playerStart.x, currentLevel.playerStart.y, 30, 50})) {
                        isSpawnSelected = true; 
                    }
                    for (int i = 0; i < currentLevel.platformCount; i++) {
                        if (CheckCollisionRecs(l, (Rectangle){currentLevel.platforms[i].x, currentLevel.platforms[i].y, currentLevel.platforms[i].width, currentLevel.platforms[i].high})) {
                            isSelected[i] = true; 
                        }
                    }
                } 
            }
            
            // --- DRAG EN COURS ---
            if (isDragging) { 
                float dx = Snap(mouseWorld.x - dragStartMouse.x, tileSize);
                float dy = Snap(mouseWorld.y - dragStartMouse.y, tileSize); 
                if (isSpawnSelected) { 
                    currentLevel.playerStart.x = initialSpawnX + dx; 
                    currentLevel.playerStart.y = initialSpawnY + dy; 
                } 
                for (int i = 0; i < currentLevel.platformCount; i++) {
                    if (isSelected[i]) { 
                        currentLevel.platforms[i].x = initialX[i] + dx; 
                        currentLevel.platforms[i].y = initialY[i] + dy; 
                        currentLevel.platforms[i].rect.x = currentLevel.platforms[i].x; 
                        currentLevel.platforms[i].rect.y = currentLevel.platforms[i].y; 
                    } 
                }
            }

            // --- REDIMENSIONNEMENT MULTIDIRECTIONNEL (MAJ + Z/W/X) ---
            if (IsKeyDown(KEY_LEFT_SHIFT) && (IsKeyDown(KEY_W) || IsKeyDown(KEY_Z) || IsKeyDown(KEY_X)) && !isLassoing && !isDragging && !isGridCreating) { 
                platResizeTimer += dt; 
                if (platResizeTimer >= repeatInterval || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)) { 
                    bool hasChanged = false;
                    for (int i = 0; i < currentLevel.platformCount; i++) {
                        if (isSelected[i]) { 
                            Platform *p = &currentLevel.platforms[i]; 
                            
                            // AGRANDIR (MAJ + W ou Z)
                            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_Z)) {
                                if (IsKeyDown(KEY_RIGHT)) { p->width += tileSize; hasChanged = true; }
                                if (IsKeyDown(KEY_LEFT)) { p->x -= tileSize; p->width += tileSize; hasChanged = true; }
                                if (IsKeyDown(KEY_DOWN)) { p->high += tileSize; hasChanged = true; }
                                if (IsKeyDown(KEY_UP)) { p->y -= tileSize; p->high += tileSize; hasChanged = true; }
                            }
                            // REDUIRE (MAJ + X) avec logique inversée !
                            else if (IsKeyDown(KEY_X)) {
                                if (IsKeyDown(KEY_LEFT) && p->width > tileSize) { p->width -= tileSize; hasChanged = true; } 
                                if (IsKeyDown(KEY_RIGHT) && p->width > tileSize) { p->x += tileSize; p->width -= tileSize; hasChanged = true; } 
                                if (IsKeyDown(KEY_UP) && p->high > tileSize) { p->high -= tileSize; hasChanged = true; } 
                                if (IsKeyDown(KEY_DOWN) && p->high > tileSize) { p->y += tileSize; p->high -= tileSize; hasChanged = true; } 
                            }

                            p->rect.x = p->x; 
                            p->rect.y = p->y;
                            p->rect.width = p->width; 
                            p->rect.height = p->high; 
                        } 
                    }
                    if (hasChanged) {
                        CommitCurrentState(); 
                        platResizeTimer = 0; 
                    }
                } 
            } else platResizeTimer = repeatInterval;

            // Creer / Delete / Save
            if (IsKeyPressed(KEY_Q) && !isGridCreating) { 
                int i = currentLevel.platformCount; 
                if (i < MAX_PLATFORMS) { 
                    strcpy(currentLevel.platforms[i].type, "BASIC_PLATFORM_S"); 
                    currentLevel.platforms[i].solid = 1; 
                    currentLevel.platforms[i].x = Snap(mouseWorld.x, tileSize); 
                    currentLevel.platforms[i].y = Snap(mouseWorld.y, tileSize); 
                    currentLevel.platforms[i].width = tileSize * 4; 
                    currentLevel.platforms[i].high = tileSize; 
                    currentLevel.platforms[i].rect = (Rectangle){currentLevel.platforms[i].x, currentLevel.platforms[i].y, currentLevel.platforms[i].width, currentLevel.platforms[i].high}; 
                    currentLevel.platformCount++; 
                    CommitCurrentState(); 
                    for (int j = 0; j < MAX_EDITOR_SELECT; j++) isSelected[j] = false; 
                    isSpawnSelected = false; 
                    isSelected[i] = true; 
                } 
            }
            
            if (IsKeyPressed(KEY_DELETE)) { 
                bool deleted = false; 
                for (int i = currentLevel.platformCount-1; i>=0; i--) {
                    if (isSelected[i]) { 
                        for (int j=i; j<currentLevel.platformCount-1; j++) { 
                            currentLevel.platforms[j] = currentLevel.platforms[j+1]; 
                            isSelected[j] = isSelected[j+1]; 
                        } 
                        currentLevel.platformCount--; 
                        deleted = true; 
                    } 
                }
                if (deleted) { 
                    CommitCurrentState(); 
                    for (int i=0; i<MAX_EDITOR_SELECT; i++) isSelected[i] = false; 
                } 
            }
            
            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) { 
                SaveLevelToJson(MAP_PATH); 
                strcpy(message, "SAUVEGARDE !"); 
                messageTimer = 90; 
            }

        } else {
            // --- LOGIQUE TEST ---
            for (int i = 0; i < currentLevel.platformCount; i++) {
                currentLevel.platforms[i].rect = (Rectangle){ currentLevel.platforms[i].x, currentLevel.platforms[i].y, currentLevel.platforms[i].width, currentLevel.platforms[i].high };
            }
            PlayerUpdate(&testPlayer, currentLevel.platforms, currentLevel.platformCount, &timeSpent, &startReload); 
            UpdateBulletPool(&playerBulletPool); 
            camera.target = testPlayer.position; 
            camera.zoom = 1.0f;
        }

        BeginDrawing();
            ClearBackground(DARKGRAY);
            BeginMode2D(camera);
                float lt = 1.0f / camera.zoom;
                
                for (int i = 0; i <= currentLevel.info.width / tileSize; i++) {
                    DrawLineEx((Vector2){(float)i*tileSize, 0}, (Vector2){(float)i*tileSize, (float)currentLevel.info.height}, lt, (i%4==0?Fade(GRAY, 0.4f):Fade(GRAY, 0.15f)));
                }
                for (int i = 0; i <= currentLevel.info.height / tileSize; i++) { 
                    float y = (float)currentLevel.info.height - (i*tileSize); 
                    DrawLineEx((Vector2){0, y}, (Vector2){(float)currentLevel.info.width, y}, lt, (i%4==0?Fade(GRAY, 0.4f):Fade(GRAY, 0.15f))); 
                }
                
                LevelDraw();
                
                for (int i = 0; i < currentLevel.platformCount; i++) { 
                    Platform *p = &currentLevel.platforms[i]; 
                    DrawRectangle(p->x, p->y, p->width, p->high, (p->solid?Fade(BLUE,0.4f):Fade(PURPLE,0.4f))); 
                    if (mode == MODE_EDITOR && isSelected[i]) {
                        DrawRectangleLinesEx((Rectangle){p->x, p->y, p->width, p->high}, 3/camera.zoom, ORANGE); 
                    } else {
                        DrawRectangleLines(p->x, p->y, p->width, p->high, p->solid?SKYBLUE:PURPLE); 
                    }
                }
                
                if (mode == MODE_EDITOR) { 
                    Rectangle sr = {currentLevel.playerStart.x, currentLevel.playerStart.y, 30, 50}; 
                    DrawRectangleRec(sr, Fade(LIME,0.6f)); 
                    DrawText("P", sr.x+8, sr.y+15, 20, DARKGREEN); 
                    if (isSpawnSelected) DrawRectangleLinesEx(sr, 3/camera.zoom, ORANGE); 
                    
                    for (int i = 0; i < currentLevel.hazardCount; i++) {
                        DrawRectangle(currentLevel.hazards[i].position.x, currentLevel.hazards[i].position.y, 32, 32, RED);
                        DrawText("H", currentLevel.hazards[i].position.x + 10, currentLevel.hazards[i].position.y + 8, 20, WHITE);
                    }
                } else { 
                    PlayerDraw(&testPlayer); 
                    DrawBulletPool(&playerBulletPool, testPlayer.position); 
                }
                
                if (isLassoing) { 
                    Rectangle r = GetLasso(lassoStart, mouseWorld); 
                    DrawRectangleRec(r, Fade(WHITE,0.1f)); 
                    DrawRectangleLinesEx(r, 2/camera.zoom, WHITE); 
                }
                else if (isGridCreating) {
                    float currentCellX = floorf(mouseWorld.x / tileSize) * tileSize;
                    float currentCellY = floorf(mouseWorld.y / tileSize) * tileSize;
                    float finalX = fminf(gridCreateStart.x, currentCellX);
                    float finalY = fminf(gridCreateStart.y, currentCellY);
                    float finalW = fabsf(currentCellX - gridCreateStart.x) + tileSize;
                    float finalH = fabsf(currentCellY - gridCreateStart.y) + tileSize;
                    Rectangle previewRec = {finalX, finalY, finalW, finalH};
                    DrawRectangleRec(previewRec, Fade(SKYBLUE, 0.4f));
                    DrawRectangleLinesEx(previewRec, 2.0f/camera.zoom, BLUE);
                }

                DrawRectangleLinesEx((Rectangle){0,0,(float)currentLevel.info.width,(float)currentLevel.info.height}, 3/camera.zoom, RED);
            EndMode2D();

            // --- UI EN HAUT À GAUCHE (CONTRÔLES STATIQUES) ---
            DrawRectangle(0, 0, 520, 320, Fade(BLACK, 0.85f));
            DrawText("EDITEUR FELL FROM HELL (v54)", 10, 10, 20, ORANGE);
            DrawText(TextFormat("MAP : %d px | BLOCS : %d/%d", currentLevel.info.height, currentLevel.platformCount, MAX_PLATFORMS), 10, 40, 18, RAYWHITE);
            DrawText("--- CONTRÔLES ---", 10, 70, 16, GRAY);
            DrawText("CLIC G. : Selection / Lasso / Drag", 10, 90, 14, LIGHTGRAY);
            DrawText("CTRL + CLIC G. GLISSE : Creer sur Grille", 10, 110, 14, SKYBLUE);
            DrawText("CTRL + C / V : Copier / Coller", 10, 130, 14, SKYBLUE);
            DrawText("ALT + DRAG : Dupliquer un bloc", 10, 150, 14, ORANGE);
            DrawText("P : Teleporter Spawn ici", 10, 170, 14, LIME);
            DrawText("Q : Nouveau Bloc | SUPPR : Effacer", 10, 190, 14, LIGHTGRAY);
            DrawText("MAJ+W/Z/X + FLECHES : Agrandir/Reduire", 10, 210, 14, LIGHTGRAY);
            DrawText("CTRL + Z / Y : Undo / Redo", 10, 230, 14, SKYBLUE);
            DrawText("CTRL + S : Sauvegarder", 10, 250, 14, ORANGE);
            DrawText("H : Centrer vue | T : MODE TEST", 10, 270, 14, RAYWHITE);
            DrawText(TextFormat("TIMELINE : %d / %d", undoPtr, maxUndo), 10, 300, 14, GRAY);

            // --- UI EN HAUT À DROITE (INFOS DYNAMIQUES DE SÉLECTION) ---
            if (mode == MODE_EDITOR) {
                int selectedCount = 0;
                int lastSelectedIdx = -1;
                for (int i = 0; i < currentLevel.platformCount; i++) {
                    if (isSelected[i]) { 
                        selectedCount++; 
                        lastSelectedIdx = i; 
                    }
                }

                DrawRectangle(GetScreenWidth() - 360, 10, 350, 65, Fade(BLACK, 0.85f));
                
                if (isSpawnSelected) {
                    DrawText("POINT DE SPAWN SELECTIONNE", GetScreenWidth() - 350 + 10, 20, 16, LIME);
                    DrawText("Touche P pour le deplacer vite", GetScreenWidth() - 350 + 10, 45, 14, GRAY);
                } 
                else if (selectedCount == 1 && lastSelectedIdx != -1) {
                    const char* st = currentLevel.platforms[lastSelectedIdx].solid ? "SOLIDE" : "TRAVERSABLE";
                    Color c = currentLevel.platforms[lastSelectedIdx].solid ? SKYBLUE : PURPLE;
                    DrawText(TextFormat("ETAT BLOC : %s", st), GetScreenWidth() - 350 + 10, 15, 20, c);
                    DrawText("(Double-clic rapide pour changer)", GetScreenWidth() - 350 + 10, 45, 14, LIGHTGRAY);
                } 
                else if (selectedCount > 1) {
                    DrawText(TextFormat("%d BLOCS SELECTIONNES", selectedCount), GetScreenWidth() - 350 + 10, 15, 20, ORANGE);
                    DrawText("(Double-clic pour tous changer)", GetScreenWidth() - 350 + 10, 45, 14, LIGHTGRAY);
                } 
                else {
                    DrawText("AUCUNE SELECTION", GetScreenWidth() - 350 + 10, 20, 18, GRAY);
                    DrawText("Cliquez sur un bloc ou faites un Lasso", GetScreenWidth() - 350 + 10, 45, 14, DARKGRAY);
                }
            }

            if (messageTimer > 0) { DrawText(message, GetScreenWidth()/2 - 100, 20, 30, GREEN); messageTimer--; }
            
            // --- FPS DÉPLACÉ EN BAS À DROITE ---
            DrawFPS(GetScreenWidth() - 100, GetScreenHeight() - 30);
        EndDrawing();
    }
    
    if (undoStack) free(undoStack); 
    CloseWindow(); 
    return 0;
}
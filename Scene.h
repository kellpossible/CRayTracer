#ifndef Scene_h
#define Scene_h
#include "Primatives.h"
#include "Camera.h"
#include "Lights.h"

typedef struct Scene Scene;

Scene* SceneCreate(char* name, Camera*);

void SceneFree(Scene* self);

void SceneAddPrimative(Scene* self, Primative* new_prim);
Primative* SceneGetPrimative(Scene* self, int index);
int SceneGetNumPrims(Scene* self);

Camera* SceneGetCamera(Scene* self);

void SceneAddLight(Scene* self, Light* new_light);
Light* SceneGetLightByIndex(Scene* self, int index);
Light* SceneGetLightByName(Scene* self, char* name);
int SceneGetNumLights(Scene* self);

void ScenePrint(Scene* self);


#endif

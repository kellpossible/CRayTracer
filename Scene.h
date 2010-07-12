#ifndef Scene_h
#define Scene_h
#include "Primatives.h"
#include "Camera.h"

#define MAXOBJS 100000

typedef struct Scene Scene;

Scene* SceneCreate(char* name, Camera*);

void SceneFree(Scene* self);

void SceneAddPrimative(Scene* self, Primative* new_prim);
Primative* SceneGetPrimative(Scene* self, int index);
int SceneGetNumPrims(Scene* self);

void ScenePrint(Scene* self);


#endif

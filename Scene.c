#include <stdlib.h>
#include <stdio.h>

#include "Primatives.h"
#include "Camera.h"
#include "Scene.h"

struct Scene {
	char* name;
	Camera* camera;
	Primative* prim_ary[MAXOBJS];
	int num_prims;
};

Scene* SceneCreate(char* name, Camera* camera){
	Scene* self = malloc(sizeof(Scene));
	self->name = name;
	self->camera = camera;
	self->num_prims = 0;
	return self;
} 

void SceneFree(Scene* self){
	free(self->name);
	free(self);
}

void SceneAddPrimative(Scene* self, Primative* new_prim){
	self->prim_ary[self->num_prims] = new_prim;
	self->num_prims+=1;
}

Primative* SceneGetPrimative(Scene* self, int index){
	if (index < self->num_prims && index >= 0){
		return self->prim_ary[index];
	}
	else return self->prim_ary[0];
}

int SceneGetNumPrims(Scene* self){
	return self->num_prims;
}

void ScenePrint(Scene* self){
	printf("Scene: %d\n", (int)self);
	printf("scene->name: %s\n", self->name);
	printf("scene->camera: %d\n\n", (int)(self->camera));
}

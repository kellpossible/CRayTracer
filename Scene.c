#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Primatives.h"
#include "Camera.h"
#include "Scene.h"

#define MAXPRIMS 100000
#define MAXLIGHTS 500

struct Scene {
	char* name;
	Camera* camera;
	Primative* prim_ary[MAXPRIMS];
	int num_prims;
	Light* light_ary[MAXLIGHTS];
	int num_lights;
};

Scene* SceneCreate(char* name, Camera* camera){
	Scene* self = malloc(sizeof(Scene));
	self->name = name;
	self->camera = camera;
	self->num_prims = 0;
	self->num_lights = 0;
	return self;
} 

void SceneFree(Scene* self){
	free(self->name);
	free(self);
}

void SceneAddPrimative(Scene* self, Primative* new_prim){
	self->prim_ary[self->num_prims] = new_prim;
	self->num_prims += 1;
}

Primative* SceneGetPrimative(Scene* self, int index){
	/*todo add error checking here if it returns a null object reference*/
	if (index < self->num_prims && index >= 0){
		return self->prim_ary[index];
	}
	else return self->prim_ary[0];//add error here
}

int SceneGetNumPrims(Scene* self){
	return self->num_prims;
}

Camera* SceneGetCamera(Scene* self){
	return self->camera;
}

void SceneAddLight(Scene* self, Light* new_light){
	self->light_ary[self->num_lights] = new_light;
	self->num_lights += 1;
}
	
Light* SceneGetLightByName(Scene* self, char* name){
	int num_lights = self->num_lights;
	int c = 0;
	while (c<num_lights){
		if (!strcmp(name, self->name)){
			return self->light_ary[0];
		}
	}
	//todo: else return error did not find light
}

Light* SceneGetLightByIndex(Scene* self, int index){
	if (index < self->num_lights && index >= 0){
		return self->light_ary[index];
	}
	else return self->light_ary[0];//todo: add error here
}

int SceneGetNumLights(Scene* self);


void ScenePrint(Scene* self){
	printf("Scene: %d\n", (int)self);
	printf("scene->name: %s\n", self->name);
	printf("scene->camera: %d\n\n", (int)(self->camera));
}

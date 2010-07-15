/* I'm actually planning to do an implementation like primitaves,
because it allows better flexibility with regard to vastly different
methods to sample light in a scene. At the moment we are stuck with
point lights.*/
#include <stdlib.h>
#include "Vectors.h"
#include "Lights.h"

struct Light {
	char* name;
	Vector3f position;
	float power;
};

Light* LightCreate(char* name, Vector3f position, float power){
	Light* self = malloc(sizeof(Light));
	self->name = name;
	self->position = position;
	self->power = power;
	return self;
}

void LightFree(Light* self){
	free(self);
}

char* LightGetName(Light* self){
	return self->name;
}

Vector3f LightGetPosition(Light* self){
	return self->position;
}
float LightGetPower(Light* self){
	return self->power;
}

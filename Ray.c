#include <stdlib.h>
#include "Ray.h"

struct Ray {
	Vector3f origin;
	Vector3f direction;
};

Ray* RayCreate(Vector3f origin, Vector3f direction){
	Ray* self = malloc(sizeof(Ray));
	self->origin = origin;
	self->direction = direction;
	return self;
}

void RayFree(Ray* self){
	free(self);
}

Vector3f RayGetOrigin(Ray* self){
	return self->origin;
}

Vector3f RayGetDirection(Ray* self){
	return self->direction;
}

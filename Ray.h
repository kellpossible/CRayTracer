#ifndef Ray_h
#define Ray_h

#include "Vectors.h"

typedef struct Ray Ray;

Ray* RayCreate(Vector3f origin, Vector3f direction);
void RayFree(Ray* self);

Vector3f RayGetOrigin(Ray* self);
Vector3f RayGetDirection(Ray* self);

#endif

#ifndef Primatives_h
#define Primatives_h

#define TYPENAMELEN 10
#include "Vectors.h"
#include "Materials.h"
#include "IntersectPoint.h"
#include "Ray.h"

typedef struct Primative Primative;
typedef struct PrimativeType PrimativeType;

/* Sphere */
Primative* PrimativeCreateSphere(Vector3f* position,
				float radius,
				Material* material);

void Sphere_free(Primative*);

float PrimSphereGetRadius(Primative*);
Vector3f* PrimSphereGetPosition(Primative*);
/* End Sphere */

/* Plane */
Primative* PrimativeCreatePlane(Vector3f* normal,
				float distance,
				Material* material);

void Plane_free(Primative*);

Vector3f PrimPlaneGetNormal(Primative*);
float PrimPlaneGetDistance(Primative*);
/* End Plane */

void PrimativeFree(Primative*);

Material* PrimativeGetMaterial(Primative*);
PrimativeType* PrimativeGetType(Primative*);
IntersectPoint* PrimativeIntersect(Primative*, Ray*);

void PrimativePrint(Primative*);


#endif
				

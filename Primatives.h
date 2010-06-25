#ifndef Primatives_h
#define Primatives_h

#define TYPENAMELEN 10
#include "Vectors.h"
#include "Materials.h"
#include "IntersectPoint.h"
#include "Ray.h"

typedef struct Primative Primative;
typedef struct PrimativeType PrimativeType;

Primative* PrimativeCreateSphere(Vector3f* position,
				float radius,
				Material* material);
float PrimSphereGetRadius(Primative*);
Vector3f* PrimSphereGetPosition(Primative*);


void PrimativeFree(Primative*);


Material* PrimativeGetMaterial(Primative*);
PrimativeType* PrimativeGetType(Primative*);
IntersectPoint* PrimativeIntersect(Primative*, Ray*);

void PrimativePrint(Primative*);


#endif
				

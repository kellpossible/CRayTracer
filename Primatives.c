#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "Primatives.h"

#include "IntersectPoint.h"
#include "Ray.h"
#include "Materials.h"
#include "Vectors.h"

struct PrimativeType {
	char* name;
	IntersectPoint* (*intersect)(Primative*, const Ray*);	
};

struct Primative {
	PrimativeType* type;
	const void* shapedata;
	Material* material;
};

/* Sphere Primative */	
struct Sphere_shapedata{
	Vector3f* position;
	float radius;
};

			
IntersectPoint* Sphere_intersect(Primative* self, const Ray* ray)
{
	float Sr, LOC, L2OC, Tca, D2, T2hc, t;
	Vector3f Ro, Rd, Sc, OC, Ri, Norm, OP, CP;
	/* t = distance along ray to intersection*/
	/* OC = ray origin -> circle origin */
	/* LOC = length(OC) */
	/* L2OC = LOC**2 */
	Ro = ray->origin;
	Rd = ray->direction;
	
	Sr = PrimSphereGetRadius(self);
	Sc = *PrimSphereGetPosition(self);
	
	//Vector3fPrint(&Sc);
	
	OC = Vector3fSub(&Sc, &Ro);
	L2OC = Vector3fDot(&OC, &OC);// Length**2
	
	Tca = Vector3fDot(&OC, &Rd); //closest approach along ray
	
	
	 
	
	/* if L2OC < Sr**2 then origin inside sphere */
	
	if (L2OC < (Sr * Sr)){//the ray origin is inside the sphere so it will hit
		D2 = L2OC - (Tca * Tca);
		/* D**2 distance from ray's closest
		approach to the sphere's center.
		*/

		T2hc = (Sr * Sr) - D2; //half chord distance squared t**2hc
	
		t = Tca + sqrt(T2hc);
		
		OP = Vector3fMulF(&Rd, t);//ray origin to point of intersection
		Ri = Vector3fAdd(&OP, &Ro);//intersect point
		CP = Vector3fSub(&Ri, &Sc);
		Norm = Vector3fDivF(&CP, Sr);
		
		IntersectPoint* ip = IntersectPointCreate(&Ri, 1);//remember to free
		return ip;
		//the ray has not hit
		/*might need to watch out for Tca == 0*/
	}
	else {//the ray is outside the sphere but it could still hit
		if (Tca > 0.0f){//it is possible fo the ray to hit
			D2 = L2OC - (Tca * Tca);
			/* D**2 distance from ray's closest
			approach to the sphere's center.
			*/
			T2hc = (Sr * Sr) - D2;
			

			T2hc = (Sr * Sr) - D2; //half chord distance squared t**2hc
			if (T2hc >= 0.0f){//the ray will definitely hit
				t = Tca - sqrt(T2hc);//distance to intersection point
				
				OP = Vector3fMulF(&Rd, t);//ray origin to point of intersection
				Ri = Vector3fAdd(&OP, &Ro);//intersect point
				printf("\nRi\n");
				Vector3fPrint(&Ri);
				printf("\n");
				
				CP = Vector3fSub(&Ri, &Sc);
				Norm = Vector3fDivF(&CP, Sr);
				
				IntersectPoint* ip = IntersectPointCreate(&Ri, 2);//remember 
				return ip;
			}
			else {//the ray definitely will not hit
				IntersectPoint* ip = IntersectPointCreateMiss();//remember to free
				return ip;
			}
		}
		else {//the ray cannot hit
			IntersectPoint* ip = IntersectPointCreateMiss();//remember to free
			return ip;
		}
	
	}
}

PrimativeType* PrimTypeSphere(void){
	PrimativeType* pt = malloc(sizeof(PrimativeType));
	pt->name = "Sphere";
	pt->intersect = Sphere_intersect;
	return pt;
}

float PrimSphereGetRadius(Primative* self){
	struct Sphere_shapedata* shapedata = (struct Sphere_shapedata *)((const void*) self->shapedata);
	printf("radius: %f\n", shapedata->radius);
	return shapedata->radius;
}

Vector3f* PrimSphereGetPosition(Primative* self){
	struct Sphere_shapedata* shapedata = (struct Sphere_shapedata *)((const void*) self->shapedata);
	Vector3fPrint(shapedata->position);
	return shapedata->position;
}

Primative* PrimativeCreateSphere(Vector3f* position,
				float radius,
				Material* material)
{
	Primative* self = malloc(sizeof(Primative));
	struct Sphere_shapedata* shapedata = malloc(sizeof(struct Sphere_shapedata));
	if (shapedata != NULL){
		shapedata->position = position;
		shapedata->radius = radius;
		if (self != NULL){
			self->type = PrimTypeSphere();
			self->shapedata = shapedata;
			self->material = material;
		}
	}
	
	return self;
}


/* End Sphere Primative */

void PrimativeFree(Primative* self){
	free((struct Sphere_shapedata*)self->shapedata);
	free(self);
}


Material* PrimativeGetMaterial(Primative* self){
	return self->material;
}

IntersectPoint* PrimativeIntersect(Primative* self, Ray* r){
	IntersectPoint* ip = self->type->intersect(self, r);
	return ip;
}

void PrimativePrint(Primative* self){
	printf("Primative: %d, Type: %s\n", (int)self, self->type->name);
}












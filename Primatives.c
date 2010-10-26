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
	IntersectPoint* (*intersect)(Primative*, Ray*);	
	void (*typefree)(Primative*);//
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

			
IntersectPoint* Sphere_intersect(Primative* self, Ray* ray)
{
	float Sr, LOC, L2OC, Tca, D2, T2hc, t;
	Vector3f Ro, Rd, Sc, OC, Ri, Norm, OP, CP;
	/* t = distance along ray to intersection*/
	/* OC = ray origin -> circle origin */
	/* LOC = length(OC) */
	/* L2OC = LOC**2 */
	Ro = RayGetOrigin(ray);
	Rd = RayGetDirection(ray);
	
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
		
		IntersectPoint* ip = IntersectPointCreate(Ri, Norm, t, 1);//remember to free
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
				//printf("\nRi\n");
				//Vector3fPrint(&Ri);
				//printf("\n");
				
				CP = Vector3fSub(&Ri, &Sc);
				Norm = Vector3fDivF(&CP, Sr);
				
				IntersectPoint* ip = IntersectPointCreate(Ri, Norm, t, 2);//remember 
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

void Sphere_free(Primative* self){
	free((struct Sphere_shapedata*)self->shapedata);
}

PrimativeType* PrimTypeSphere(void){
	PrimativeType* pt = malloc(sizeof(PrimativeType));
	pt->name = "Sphere";
	pt->intersect = Sphere_intersect;
	pt->typefree = Sphere_free;
	return pt;
}

float PrimSphereGetRadius(Primative* self){
	struct Sphere_shapedata* shapedata = (struct Sphere_shapedata *)((const void*) self->shapedata);
	//printf("radius: %f\n", shapedata->radius);
	return shapedata->radius;
}

Vector3f* PrimSphereGetPosition(Primative* self){
	struct Sphere_shapedata* shapedata = (struct Sphere_shapedata *)((const void*) self->shapedata);
	//Vector3fPrint(shapedata->position);
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


/* Triangle Primative
struct Triangle_shapedata{
	
}

End Triangle Primative */

/* Plane Primative */
struct Plane_shapedata{
	Vector3f normal;
	float distance;//distance from origin
};

IntersectPoint* Plane_intersect(Primative* self, Ray* r){
	Vector3f Ro = RayGetOrigin(r);
	Vector3f Rd = RayGetDirection(r);
	Vector3f Pn = PrimPlaneGetNormal(self);
	float D = -1.0f * PrimPlaneGetDistance(self);
	
	float Vd = Vector3fDot(&Pn, &Rd);
	if (Vd < -0.00001f && Vd > 0.00001f)
	{
		return IntersectPointCreateMiss();
	}
	if (Vd > 0.0f)//backface culling not sure if this is good idea...
	{
		return IntersectPointCreateMiss();
	}
	
	float Vo = -1.0f * (Vector3fDot(&Pn, &Ro) + D);
	float t = Vo/Vd;//might need FDIV
	if (t < 0)
	{
		return IntersectPointCreateMiss();
	}
	/*
	R(t) = Ro + Rd*t
	*/
	
	Rd = Vector3fMulF(&Rd, t);//multiply Rd by t
	Vector3f ri = Vector3fAdd(&Ro, &Rd);
	return IntersectPointCreate(ri, Pn, t, 2);
}

void Plane_free(Primative* self){
	free((struct Plane_shapedata*)self->shapedata);
}


PrimativeType* PrimTypePlane(void){
	PrimativeType* pt = malloc(sizeof(PrimativeType));
	pt->name = "Plane";
	pt->intersect = Plane_intersect;
	pt->typefree = Plane_free;
	return pt;
}

Primative* PrimativeCreatePlane(Vector3f* normal,
				float distance,
				Material* material){
	Primative* self = malloc(sizeof(Primative));
	struct Plane_shapedata* shapedata = malloc(sizeof(struct Plane_shapedata));
	if (shapedata != NULL){
		shapedata->normal = *normal;
		shapedata->distance = distance;
		if (self != NULL){
			self->type = PrimTypePlane();
			self->shapedata = shapedata;
			self->material = material;
		}
	}
	return self;
}

Vector3f PrimPlaneGetNormal(Primative* self){
	struct Plane_shapedata* shapedata = (struct Plane_shapedata *)((const void*) self->shapedata);
	return shapedata->normal;
}

float PrimPlaneGetDistance(Primative* self){
	struct Plane_shapedata* shapedata = (struct Plane_shapedata *)((const void*) self->shapedata);
	return shapedata->distance;
}

/* End Plane Primative */

void PrimativeFree(Primative* self){
	self->type->typefree(self);
	free(self->type);
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












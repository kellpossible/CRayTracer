#include "Primatives.h"
#include "Materials.h"
#include "Vectors.h"
#include "IntersectPoint.h"
#include "Ray.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Vector3f v1 = {{0.0f, 6.0f, 0.0f}};
	Material* mat = MaterialDefault();
	Primative* p = PrimativeCreateSphere(&v1, 1.0f, mat);
	PrimativePrint(p);
	Material* m = PrimativeGetMaterial(p);
	printf("%s\n", MaterialGetName(m));
	
	
	Vector3f pos = {{0.0f, 0.0f, 0.0f}};
	Vector3f dir = {{0.0f, 1.0f, 0.0f}};
	Ray* r = RayCreate(pos, dir);
	IntersectPoint* ip =  PrimativeIntersect(p, r);
	
	printf("\nHIT DATA: \n");
	Vector3fPrint(IntersectPointGetPos(ip));
	int hit_type = IntersectPointGetType(ip);
	printf("hit_type: %d\n\n", hit_type);
	
	IntersectPointFree(ip);
	PrimativeFree(p);
	free(mat);
	free(p);
	free(m);
	RayFree(r);
	return 0;
}

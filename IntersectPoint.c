#include <stdlib.h>
#include <stdio.h>

#include "IntersectPoint.h"
#include "Vectors.h"
#include "Ray.h"

struct IntersectPoint{
	Vector3f position;//some real problems here (might need to make ths a pointer instead
	Vector3f normal;
	float distance;//distance from camera
	int type; 
};

IntersectPoint* IntersectPointCreate(	const Vector3f position,
					 const Vector3f normal,
					 float distance,
					 int type){
	IntersectPoint* ip = malloc(sizeof(IntersectPoint));
	//IntersectPoint ip;
	ip->position = position;//some problem with storing position as a pointer
	ip->normal = normal;
	ip->distance = distance;
	ip->type = type;
	//printf("\nCreatingIPpos:\n");
	//Vector3fPrint(IntersectPointGetPos(ip));
	//printf("\n");
	
	return ip;
}
IntersectPoint* IntersectPointCreateMiss(void){
	IntersectPoint* ip = IntersectPointCreate(Vector3fZERO, Vector3fZERO, 0.0f, 0);
	return ip;
}
void IntersectPointFree(IntersectPoint* ip){
	free(ip);
}

Vector3f* IntersectPointGetPos(IntersectPoint* ip){
	Vector3f* retv = &(ip->position);
	return retv;
}

Vector3f IntersectPointGetNormal(IntersectPoint* self){
	return self->normal;
}

float IntersectPointGetDistance(IntersectPoint* self){
	return self->distance;
}

int IntersectPointGetType(IntersectPoint* ip){
	return ip->type;
}

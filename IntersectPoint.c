#include <stdlib.h>
#include <stdio.h>

#include "IntersectPoint.h"
#include "Vectors.h"
#include "Ray.h"

struct IntersectPoint{
	Vector3f position;//some real problems here (might need to make ths a pointer instead
	Vector3f normal;
	int type; 
};

IntersectPoint* IntersectPointCreate(const Vector3f position, const Vector3f normal,int type){
	IntersectPoint* ip = malloc(sizeof(IntersectPoint));
	//IntersectPoint ip;
	ip->position = position;//some problem with storing position as a pointer
	ip->normal = normal;
	ip->type = type;
	
	//printf("\nCreatingIPpos:\n");
	//Vector3fPrint(IntersectPointGetPos(ip));
	//printf("\n");
	
	return ip;
}
IntersectPoint* IntersectPointCreateMiss(void){
	IntersectPoint* ip = malloc(sizeof(IntersectPoint));
	ip->position = Vector3fZERO;
	ip->normal = Vector3fZERO;
	ip->type = 0;
	return ip;
}
void IntersectPointFree(IntersectPoint* ip){
	free(ip);
}

Vector3f* IntersectPointGetPos(IntersectPoint* ip){
	Vector3f* retv = &(ip->position);
	return retv;
}

int IntersectPointGetType(IntersectPoint* ip){
	return ip->type;
}

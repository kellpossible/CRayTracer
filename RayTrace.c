#include "IntersectPoint.h"
#include "Primatives.h"
#include "Ray.h"
#include "RayTrace.h"

int RayTrace(Ray* r, Scene* s){
	Primative* prim = SceneGetPrimative(s, 0);
	IntersectPoint* ip = PrimativeIntersect(prim, r);
	return IntersectPointGetType(ip);
	/*
	if (IntersectPointGetType(ip) > 0){
		Vector3f col = {{1.0f, 1.0f, 1.0f}};
		return col;
	}
	else{
		Vector3f col = {{0.0f, 0.0f, 0.0f}};
		return col;
	}*/
}

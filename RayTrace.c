#include <stdio.h>
#include "IntersectPoint.h"
#include "Primatives.h"
#include "Materials.h"
#include "Ray.h"
#include "RayTrace.h"
#include "Lights.h"

Vector3f RayTrace(Ray* r, Scene* s){
	Primative* prim = SceneGetPrimative(s, 0);
	IntersectPoint* ip = PrimativeIntersect(prim, r);
	Light* light = SceneGetLightByIndex(s, 0);
	
	Vector3f light_pos = LightGetPosition(light);
	Vector3f iptolight = Vector3fSub(&light_pos, IntersectPointGetPos(ip));
	Vector3f light_dir = Vector3fNormalize(&iptolight);
	
	if (IntersectPointGetType(ip) > 0){
		Material* mat = PrimativeGetMaterial(prim);
		
		//return MaterialGetColour(mat);
		return MaterialLambertDiffuse(mat, 
				light,
				light_dir,
				IntersectPointGetNormal(ip));
	}
	else{
		Vector3f col = {{0.0f, 0.0f, 0.0f}};
		return col;
	}
}

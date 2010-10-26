#include <stdio.h>
#include "IntersectPoint.h"
#include "Primatives.h"
#include "Materials.h"
#include "Ray.h"
#include "RayTrace.h"
#include "Lights.h"
#include "Scene.h"

#define MAXIP 200

Vector3f RayTrace(Ray* r, Scene* s){
	/*two symetrical arrays for storing references
	and connections between primatives and intersection
	points. probably better done using real references
	but this is all I can get to work at the moment.*/
	
	
	IntersectPoint* ip_ary[MAXIP];
	Primative* prim_ary[MAXIP];
	
	Primative* temp_prim;
	IntersectPoint* ip;
	
	Light* light = SceneGetLightByIndex(s, 0);
	
	int num_prims = SceneGetNumPrims(s);
	int prim_index = 0;
	int num_ip_found = 0;
	while (prim_index < num_prims)
	{
		temp_prim = SceneGetPrimative(s, prim_index);
		ip = PrimativeIntersect(temp_prim, r);
		
/*		PrimativePrint(temp_prim);*/
/*		printf("raydir:  ");*/
/*		Vector3f ray_dir = RayGetDirection(r);*/
/*		Vector3fPrint(&ray_dir);*/
/*		printf("raypos:  ");*/
/*		Vector3f ray_pos = RayGetOrigin(r);*/
/*		Vector3fPrint(&ray_pos);*/
/*		printf("iptype = %d\n", IntersectPointGetType(ip));*/
		
		if (IntersectPointGetType(ip) > 0){
/*			printf("ipdistance = %f\n", IntersectPointGetDistance(ip));*/
/*			printf("ip position: \n");*/
			ip_ary[num_ip_found] = ip;
			prim_ary[num_ip_found] = temp_prim;
			num_ip_found += 1;
		}
		prim_index+=1;
	}
	
	if (num_ip_found == 0)
	{
		Vector3f col = {{0.0f, 0.0f, 0.0f}};//black area behind primatives
		return col;
	}
	else
	{
		/*dumb distance sorting algorithm*/
		int closest_ip_index = 0;//starting closest
		int ip_index = 1;//offset index
		while (ip_index < num_ip_found)
		{
			ip = ip_ary[ip_index];
			float d1 = IntersectPointGetDistance(ip);
			ip = ip_ary[closest_ip_index];
			float d2 = IntersectPointGetDistance(ip);
			if (d1 < d2)
			{
				closest_ip_index = ip_index;
			}
			ip_index +=1;
		}
		
		/*light calculation section*/
		Primative* closest_prim = prim_ary[closest_ip_index];
		IntersectPoint* closest_ip = ip_ary[closest_ip_index];
		
		Vector3f light_pos = LightGetPosition(light);
		Vector3f iptolight = Vector3fSub(&light_pos, IntersectPointGetPos(closest_ip));
		Vector3f light_dir = Vector3fNormalize(&iptolight);
	
		Material* mat = PrimativeGetMaterial(closest_prim);

		//return MaterialGetColour(mat);
		return MaterialLambertDiffuse(	mat, 
						light,
						light_dir,
						IntersectPointGetNormal(closest_ip));
	}
}

#include <stdio.h>
#include "Ray.h"
#include "Primatives.h"
#include "Vectors.h"
#include "IntersectPoint.h"
#include "RayTrace.h"

int main (int argc, char *argv[])
{
	Vector3f colour_yellow = {{0.8f, 0.8f, 0.1f}};
	Material* mat_yellow = MaterialCreate("yellow", colour_yellow);
	
	Vector3f plane1_dir = {{0.0f, 0.0f, 1.0f}};
	Primative* plane1 = PrimativeCreatePlane(&plane1_dir, 0.0f, mat_yellow);
	
	Vector3f ray_dir = {{0.0f,2.0f,-1.0f}};
	ray_dir = Vector3fNormalize(&ray_dir);
	Vector3f ray_or = {{0.0f, 0.0f, 2.0f}};
	Ray* r = RayCreate(ray_or, ray_dir);
	
	IntersectPoint* ip = PrimativeIntersect(plane1, r);
	int ip_type = IntersectPointGetType(ip);
	float ip_dist = IntersectPointGetDistance(ip);
	Vector3f* ip_pos = IntersectPointGetPos(ip);
	
	printf("iptype = %d\n", ip_type);
	printf("ipdistance = %f\n", ip_dist);
	printf("ip position: \n");
	Vector3fPrint(ip_pos);
	
	return 0;
}

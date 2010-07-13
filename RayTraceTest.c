#include <stdio.h>
#include <stdlib.h>
#include "Screen.h"
#include "Vectors.h"
#include "View.h"
#include "Primatives.h"
#include "Ray.h"
#include "Materials.h"
#include "Scene.h"
#include "IntersectPoint.h"
#include <string.h>
/* expected output: */
/* */

int trace_ray(Ray r, Scene* s){
	IntersectPoint* ip = PrimativeIntersect(s->primative, &r);
	return IntersectPointGetType(ip);
}

int main(int argc, char* argv[]){
	int i;
	float spherexpos = 2.0f;
	float sphereradius = 0.5f;
	for (i = 0; i < argc; ++i){
		if (i >= 1){
			if (!strcmp(argv[i], "SphereXPos")){
				puts(argv[i + 1]);
				spherexpos = (float)(stringtoint(argv[i + 1]));
				printf("%.2f\n", spherexpos);
			}
		}
	}
	printf("TESTING: %i\n", stringtoint("-21"));
	Vector3f camera1_pos = {{0.0f, 0.0f, 0.0f}};
	Vector3f camera1_tar = {{2.0f, 0.0f, 0.0f}};
	float camera1_focal = 1.0f;
	View* camera1 = ViewCreate(&camera1_pos, &camera1_tar, camera1_focal);
	//ViewPrint(camera1);
	
	Screen* screen1 = ScreenCreate(1.0f, 18, 18, camera1);
	//ScreenPrint(screen1);
	
	Vector3f sphere_pos = {{spherexpos, 0.0f, 0.0f}};
	Material mat = {"red"};
	Primative* prim1 = PrimativeCreateSphere(&sphere_pos, 0.5f, &mat);
	
	Scene* scene1 = malloc(sizeof(Scene));
	scene1->camera = camera1;
	scene1->primative = prim1;
	scene1->screen = screen1;
	
	
	int y = 0;
	int x;
	Vector3f ray_vec, ray_norm, ray_pos;
	Pixel curr_pix;
	
	while (y < 18){
		x = 0;
		while (x < 18){
			curr_pix = ScreenGetPixel(screen1, x, y);
			ray_pos = PixelGetPosition(&curr_pix);
			ray_vec = Vector3fSub(&ray_pos, &camera1_pos);
			ray_norm = Vector3fNormalize(&ray_vec);
			Ray r = {ray_pos, ray_norm};
			printf("%i ", trace_ray(r, scene1)); 
			x++;
		}
		printf("\n");
		y++;
	}
	
	ScreenFree(screen1);
	ViewFree(camera1);
	
	return 0;
}

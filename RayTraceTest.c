#include <stdio.h>
#include <stdlib.h>
#include "Screen.h"
#include "Vectors.h"
#include "Camera.h"
#include "Primatives.h"
#include "Scene.h"
#include "IntersectPoint.h"
#include "RayTrace.h"
/* expected output: */
/* */

int main(int argc, char* argv[]){
	int i;
	int im_size = 30;
	Vector3f camera1_pos = {{0.0f, 0.0f, 0.0f}};
	Vector3f camera1_tar = {{2.0f, 0.0f, 0.0f}};
	float camera1_focal = 1.0f;
	Screen* screen1 = ScreenCreate(1.0f, im_size, im_size);
	Camera* camera1 = CameraCreate(screen1, &camera1_pos, &camera1_tar, camera1_focal);
	//ViewPrint(camera1);
	
	Vector3f sphere_pos = {{6.0f, 0.0f, 0.0f}};
	Material mat = {"red"};
	Primative* prim1 = PrimativeCreateSphere(&sphere_pos, 2.0f, &mat);
	
	Scene* scene1 = SceneCreate("Scene1", camera1);
	SceneAddPrimative(scene1, prim1);
	/*todo:
	need to add an error check for when primative doesn't exist when using
	SceneGetPrimative.*/
	
	
	int y = 0;
	int x;
	Vector3f ray_vec, ray_norm, ray_pos;
	Pixel curr_pix;
	
	while (y < ScreenGetImageHeight(screen1)){
		x = 0;
		while (x < ScreenGetImageWidth(screen1)){
			curr_pix = ScreenGetPixel(screen1, x, y);
			ray_pos = PixelGetPosition(&curr_pix);
			ray_vec = Vector3fSub(&ray_pos, &camera1_pos);
			ray_norm = Vector3fNormalize(&ray_vec);
			Ray* r = RayCreate(ray_pos, ray_norm);
			printf("%i ",RayTrace(r, scene1)); 
			RayFree(r);
			x++;
		}
		printf("\n");
		y++;
	}
	
	ScreenFree(screen1);
	CameraFree(camera1);
	PrimativeFree(prim1);
	
	return 0;
}

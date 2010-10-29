#include <stdio.h>
#include <stdlib.h>
#include "Screen.h"
#include "Vectors.h"
#include "Camera.h"
#include "Primatives.h"
#include "Scene.h"
#include "IntersectPoint.h"
#include "RayTrace.h"
#include "Sample.h"
#include "Image.h"
#include "Materials.h"
#include "Lights.h"

/* expected output: */
/* */


int main(int argc, char* argv[]){
	int i;
	int im_size = 500;
	/*TODO: fix camera maths/screen building maths
	to include rotations, and stop screwing up when I change
	the position or focal length*/
	Vector3f camera1_pos = {{0.0f, -10.0f, 1.0f}};
	Vector3f camera1_tar = {{0.0f, 1.0f, -2.0f}};
	float camera1_angle = 0.0f;
	float camera1_focal = 1.0f;
	Screen* screen1 = ScreenCreate(1.0f, im_size, im_size);
	Camera* camera1 = CameraCreate(screen1, &camera1_pos, &camera1_tar, camera1_focal, camera1_angle);
	CameraPrint(camera1);
	
	Vector3f colour_red = {{0.8f, 0.1f, 0.1f}};
	Material* mat_red = MaterialCreate("red", colour_red);
	
	Vector3f colour_green = {{0.1f, 0.8f, 0.1f}};
	Material* mat_green = MaterialCreate("green", colour_green);
	
	Vector3f colour_yellow = {{1.0f, 1.0f, 1.0f}};
	Material* mat_yellow = MaterialCreate("yellow", colour_yellow);
	
	Vector3f sphere1_pos = {{0.0f, 0.0f, 0.0f}};
	Primative* prim1 = PrimativeCreateSphere(&sphere1_pos, 1.0f, mat_red);
	
	Vector3f sphere2_pos = {{0.0f, 0.0f, 2.0f}};
	Primative* prim2 = PrimativeCreateSphere(&sphere2_pos, 0.8f, mat_green);
	
	Vector3f plane1_dir = {{0.0f, 0.0f, 1.0f}};
	Primative* plane1 = PrimativeCreatePlane(&plane1_dir, -3.0f, mat_yellow);
	
	Scene* scene1 = SceneCreate("Scene1", camera1);
	SceneAddPrimative(scene1, prim1);
	SceneAddPrimative(scene1, prim2);
	SceneAddPrimative(scene1, plane1);
	
	Vector3f light_pos = {{0.0f, -5.0f, 3.0f}};
	Light* light1 = LightCreate("Light1", light_pos, 0.1f); 
	SceneAddLight(scene1, light1);
	/*TODO:
	need to add an error check for when primative doesn't exist when using
	SceneGetPrimative.*/
	
	Image* im = SampleSimple(scene1);//main raytracing
	ImageWriteFilePPM3(im,"RayTraceTest.ppm");
	printf("Image Written to RayTraceTest.ppm\n");
	
	LightFree(light1);
	MaterialFree(mat_red);
	MaterialFree(mat_yellow);
	MaterialFree(mat_green);
	ImageFree(im);	
	ScreenFree(screen1);
	CameraFree(camera1);
	PrimativeFree(prim1);
	PrimativeFree(prim2);
	PrimativeFree(plane1);
	
	return 0;
}

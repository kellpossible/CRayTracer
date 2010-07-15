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
	int im_size = 2000;
	Vector3f camera1_pos = {{0.0f, 0.0f, 0.0f}};
	Vector3f camera1_tar = {{2.0f, 0.0f, 0.0f}};
	float camera1_focal = 1.0f;
	Screen* screen1 = ScreenCreate(1.0f, im_size, im_size);
	Camera* camera1 = CameraCreate(screen1, &camera1_pos, &camera1_tar, camera1_focal);
	//ViewPrint(camera1);
	
	Vector3f colour = {{0.8f, 0.1f, 0.1f}};
	Material* mat = MaterialCreate("red", colour);
	
	Vector3f sphere_pos = {{3.0f, 0.0f, 0.0f}};
	Primative* prim1 = PrimativeCreateSphere(&sphere_pos, 1.0f, mat);
	
	Scene* scene1 = SceneCreate("Scene1", camera1);
	SceneAddPrimative(scene1, prim1);
	
	Vector3f light_pos = {{0.0f, .0f, 3.0f}};
	Light* light1 = LightCreate("Light1", light_pos, 0.1f); 
	SceneAddLight(scene1, light1);
	/*TODO:
	need to add an error check for when primative doesn't exist when using
	SceneGetPrimative.*/
	
	Image* im = SampleSimple(scene1);//main raytracing
	ImageWriteFilePPM3(im,"RayTraceTest.ppm");
	printf("Image Written to RayTraceTest.ppm\n");
	
	LightFree(light1);
	MaterialFree(mat);
	ImageFree(im);	
	ScreenFree(screen1);
	CameraFree(camera1);
	PrimativeFree(prim1);
	
	return 0;
}

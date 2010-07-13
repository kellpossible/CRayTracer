#include <stdio.h>
#include "Screen.h"
#include "Vectors.h"
#include "Scene.h"
#include "Camera.h"
#include "Primatives.h"

/* expected output: */
/* */


int main(){
	Vector3f camera1_pos = {{0.0f, 0.0f, 0.0f}};
	Vector3f camera1_tar = {{2.0f, 0.0f, 0.0f}};
	float camera1_focal = 1.0f;
	Screen* screen1 = ScreenCreate(1.0f, 1000, 1000);
	Camera* camera1 = CameraCreate(screen1, &camera1_pos, &camera1_tar, camera1_focal);
	

	Scene* scene1 = SceneCreate("scene1", camera1);
	
	CameraFree(camera1);
	ScreenFree(screen1);
	
	return 0;
}

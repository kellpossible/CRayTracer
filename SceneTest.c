#include <stdio.h>
#include "Screen.h"
#include "Vectors.h"
#include "View.h"
#include "Scene.h"
#include "Camera.h"
#include "Primatives.h"

/* expected output: */
/* */


int main(){
	Vector3f view1_pos = {{0.0f, 0.0f, 0.0f}};
	Vector3f view1_tar = {{2.0f, 0.0f, 0.0f}};
	float view1_focal = 1.0f;
	View* view1 = ViewCreate(&view1_pos, &view1_tar, view1_focal);
	ViewPrint(view1);
	
	Screen* screen1 = ScreenCreate(1.0f, 1000, 1000, view1);
	ScreenPrint(screen1);
	
	Camera* camera1 = CameraCreate(view1, screen1);
	
	Scene* scene1 = SceneCreate("scene1", camera1);
	
	CameraFree(camera1);
	ScreenFree(screen1);
	ViewFree(view1);
	
	return 0;
}

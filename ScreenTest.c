#include <stdio.h>
#include "Screen.h"
#include "Vectors.h"
#include "View.h"

/* expected output: */
/* */


int main(){
	Vector3f camera1_pos = {{0.0f, 0.0f, 0.0f}};
	Vector3f camera1_tar = {{2.0f, 0.0f, 0.0f}};
	float camera1_focal = 1.0f;
	View* camera1 = ViewCreate(&camera1_pos, &camera1_tar, camera1_focal);
	ViewPrint(camera1);
	
	Screen* screen1 = ScreenCreate(1.0f, 1000, 1000, camera1);
	ScreenPrint(screen1);
	ScreenFree(screen1);

	
	ViewFree(camera1);
	
	return 0;
}

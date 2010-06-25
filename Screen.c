#include <stdlib.h>
#include <stdio.h>

#include "Screen.h"
#include "Vectors.h"
#include "View.h"

#define MAXIMAGESIZE 10000

struct Pixel {
	int x;
	int y;
	Vector3f position;
	Vector3f colour;
};

struct Screen {
	float width;
	int image_width;
	int image_height;
	
	View* view;
	Vector3f position;
	
	float pixel_width;
	Pixel* pixel_rows[MAXIMAGESIZE];
};
/*
struct PixelSample {
	Vector3f position;
	Colour colour;
	
*/

Screen* ScreenCreate(float width, int image_width, int image_height, View* view){
	float pixel_width, height;
	Vector3f cam_pos;
	Vector3f view_vec;
	Vector3f vup_dir = {{0.0f, 0.0f, 1.0f}};
	Vector3f vup, vleft, vleft_norm, vright, vright_inc, vdown_inc; //vectors from centre of screen to edges
	Screen* self = malloc(sizeof(Screen));
	
	self->width = width;
	self->image_width = image_width;
	self->image_height = image_height;
	
	self->view = view;
	cam_pos = ViewGetPosition(view);
	view_vec = ViewGetViewVector(view);
	self->position = Vector3fAdd(&cam_pos, &view_vec);
	
	
	pixel_width = width/((float)image_width);
	self->pixel_width = pixel_width;
	
	height = pixel_width * image_height;
	vup = Vector3fMulF(&vup_dir, (height/2.0f));//from screen center
	vleft = Vector3fCross(&vup, &view_vec);
	vleft_norm = Vector3fNormalize(&vleft);
	
	vright = Vector3fNeg(&vleft_norm);//vright norm
	vright = Vector3fMulF(&vright, (width/2.0f));//final vright
	//potential for optimization around here
	
	vright_inc = Vector3fMulF(&vright, pixel_width);
	/*creation of the image array*/
	
	
	int counter_rows = 0;
	while (counter_rows < image_height){
		int counter_pixels = 0;
		while (counter_pixels < image_width){
			
		}
	}
	
	printf("\nvleft:\n");
	Vector3fPrint(&vleft);
	printf("\n");
	return self;
}

void ScreenFree(Screen* self){
	free(self);
}

/*Pixel* ScreenCreatePixelRows(Screen* self){
	
}*/

void ScreenPrint(Screen* self){
	printf("\nScreen %i Stats:\n", (int)self);
	printf("Screen Width: %.3f\n", self->width);
	printf("Image Width: %i, Image Height: %i\n", self->image_width, self->image_height);
	printf("View: %i\n", (int)self->view);
	printf("Position: ");
	Vector3fPrint(&self->position);
	printf("Pixel Width: %.3f\n", self->pixel_width);
}


Pixel PixelCreate(int x, int y, Vector3f* position){
	Vector3f colour = {{0.0f, 0.0f, 0.0f}};
	Pixel p = {x, y, *position, colour};
	return p;
} 





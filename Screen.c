#include <stdlib.h>
#include <stdio.h>

#include "Screen.h"
#include "Vectors.h"
#include "View.h"

#define MAXIMAGESIZE 5000

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
	Pixel pixel_array[MAXIMAGESIZE][MAXIMAGESIZE];//can probably be more dynamic
};
/*
struct PixelSample {
	Vector3f position;
	Colour colour;
	
*/

Screen* ScreenCreate(float width, int image_width, int image_height, View* view){
	float pixel_width, height;
	//todo:
	//if pixel_width < MAXIMAGESIZE raise error
	Vector3f cam_pos;
	Vector3f view_vec;
	Vector3f vup_dir = {{0.0f, 0.0f, 1.0f}};
	Vector3f vup, vleft, vleft_norm, vright, vright_inc, vdown_inc, vup_norm; 
	//vectors from centre of screen to edges
	Vector3f vpixvertical, vpixhorizontal;// pixel construction vectors
	
	Screen* self = malloc(sizeof(Screen));
	
	self->width = width;//real width
	self->image_width = image_width;//width in pixels
	self->image_height = image_height;//height in pixels
	
	self->view = view;
	cam_pos = ViewGetPosition(view);
	view_vec = ViewGetViewVector(view);
	self->position = Vector3fAdd(&cam_pos, &view_vec);
	
	
	pixel_width = width/((float)image_width);
	self->pixel_width = pixel_width;
	
	height = pixel_width * image_height;
	vup = Vector3fMulF(&vup_dir, (height/2.0f));//from screen center
	vup_norm = Vector3fNormalize(&vup);
	vdown_inc = Vector3fMulF(&vup_norm, (-1.0f * pixel_width));
	
	vleft = Vector3fCross(&vup, &view_vec);//final vleft
	vleft_norm = Vector3fNormalize(&vleft);
	
	vright = Vector3fNeg(&vleft_norm);//vright norm
	//potential for optimization around here
	
	vright_inc = Vector3fMulF(&vright, pixel_width);//vright increment
	
	/*creation of the image array*/
	//should probably make a new type called pixel array
	//will do when refactor for montecarlo sampling arrives
	/* Example
	
	<- vleft
		_____________________	
		|1, 2, 3, 4,  5,  6 |
		|7, 8, 9, 10, 11, 12|
	vup ^   _____________________
	*/
	/*debug info
	printf("\nvleft:\n");
	Vector3fPrint(&vleft);
	printf("\nvleft_norm:\n");
	Vector3fPrint(&vleft_norm);
	printf("\nvright:\n");
	Vector3fPrint(&vright);
	printf("\nvright_inc:\n");
	Vector3fPrint(&vright_inc);
	printf("\nvdown_inc:\n");
	Vector3fPrint(&vdown_inc);
	*/
	int counter_rows = 0;
	vpixvertical = vup;//initial vpixvertical
	
	printf("\ninitial vpixvert:\n");
	Vector3fPrint(&vpixvertical);
	
	//starting top left with a biased sampling and moving right
	//with vright increments
	while (counter_rows < image_height){
		int counter_pixels = 0;
		vpixvertical = Vector3fAdd(&vpixvertical, &vdown_inc);//all shifted down one maybe needs offset!
		// I think it is better performance adding an increment
		vpixhorizontal = Vector3fSub(&vleft, &vright_inc);//resetting to left hand edge 
		//(subtracting offset as well)
		
		while (counter_pixels < image_width){
			vpixhorizontal = Vector3fAdd(&vpixhorizontal, &vright_inc);
			Vector3f pixpos = Vector3fAdd(&vpixhorizontal, &vpixvertical);
			pixpos = Vector3fAdd(&pixpos, &(self->position));//adjust according to screen position
			self->pixel_array[counter_rows][counter_pixels] = PixelCreate(	counter_pixels, 
											counter_rows, 
											pixpos);
			//for better performance work with pointers -- when new type arrives
			counter_pixels += 1;
		}
		counter_rows += 1;
	}
	
	
	printf("\n");
	return self;
}

void ScreenFree(Screen* self){//needs to cycle through all the pixels and free them
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
	/*
	int y = 0;
	Pixel p;
	int x;
	while (y < self->image_height){
		x = 0;
		while (x < self->image_width){
			p = self->pixel_array[y][x];
			Vector3fPrint(&(p.position));
			x += 1;
		}
		y += 1;
	}*/
}


Pixel PixelCreate(int x, int y, Vector3f position){
	Vector3f colour = {{0.0f, 0.0f, 0.0f}};
	Pixel p = {x, y, position, colour};
	return p;
} 





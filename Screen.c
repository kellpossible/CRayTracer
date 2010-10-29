#include <stdlib.h>
#include <stdio.h>

#include "Screen.h"
#include "Vectors.h"
#include "Colours.h"

#define MAXIMAGESIZE 5000

struct Screen {
	float width;
	int image_width;
	int image_height;
	
	Vector3f position;
        Vector3f up; //vector to top side of the screen
        Vector3f left;// vecort to left side of the screen
        Vector3f left_dir;
        Vector3f up_dir;
	
	float pixel_width;
	Pixel pixel_array[MAXIMAGESIZE][MAXIMAGESIZE];//can probably be more dynamic
};
/*
struct PixelSample {
	Vector3f position;
	Colour colour;
	
*/

Screen* ScreenCreate(float width, int image_width, int image_height){
	Screen* self = malloc(sizeof(Screen));
	
	self->width = width;//real width
	self->image_width = image_width;//width in pixels
	self->image_height = image_height;//height in pixels
	return self;
	
}

void ScreenCalibrate(Screen* self, Vector3f cam_pos, Vector3f view_vec, float view_angle){
	float pixel_width, height;
	//todo:
	//if pixel_width < MAXIMAGESIZE raise error
	Vector3f SceneUp = {{0.0f, 0.0f, 1.0f}};
        Vector3f RightRel, RightRelRotate, UpRotate, BackRel, UpRelRotate;
	Vector3f DownRelRotate, ScreenUpDir, ScreenUp, ScreenLeft, ScreenLeftDir;
        Vector3f ScreenDownInc, ScreenRightDir, ScreenRightInc;
	//vectors from centre of screen to edges
	Vector3f vpixvertical, vpixhorizontal;// pixel construction vectors
	
	self->position = Vector3fAdd(&cam_pos, &view_vec);
	
        RightRel = Vector3fCross(&SceneUp, &view_vec);
        BackRel = Vector3fCross(&SceneUp, &RightRel);
        //UpRotate = RotateAroundVector(SceneUp, view_angle, BackRel);//rotate scene up around backrel
        UpRotate = SceneUp;
        RightRelRotate = Vector3fCross(&UpRotate, &view_vec);
        DownRelRotate = Vector3fCross(&RightRelRotate, &view_vec);
        UpRelRotate = Vector3fNeg(&DownRelRotate);

        ScreenUpDir = Vector3fNormalize(&UpRelRotate);

        


        /* begin old code */

	pixel_width = (self->width)/((float)(self->image_width));
	self->pixel_width = pixel_width;
	height = pixel_width * (self->image_height);
        
	ScreenUp = Vector3fMulF(&ScreenUpDir, (height/2.0f));

        self->up = ScreenUp;
        self->up_dir = ScreenUpDir;

	ScreenDownInc = Vector3fMulF(&ScreenUpDir, (-1.0f * pixel_width));
	
	ScreenLeftDir = Vector3fCross(&ScreenUp, &view_vec);//final vleft
	ScreenLeftDir = Vector3fNormalize(&ScreenLeftDir);
        ScreenLeft = Vector3fMulF(&ScreenLeftDir, (self->width/2.0f));
        
        self->left = ScreenLeft;
        self->left_dir = ScreenLeftDir;

	ScreenRightDir = Vector3fNeg(&ScreenLeftDir);//vright norm
	//potential for optimization around here
	
	ScreenRightInc = Vector3fMulF(&ScreenRightDir, pixel_width);//vright increment

        printf("up: ");
        Vector3fPrint(&ScreenLeft);

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
	vpixvertical = ScreenUp;//initial vpixvertical
	
	//printf("\ninitial vpixvert:\n");
	//Vector3fPrint(&vpixvertical);
	
	//starting top left with a biased sampling and moving right
	//with vright increments
	while (counter_rows < (self->image_height)){
		int counter_pixels = 0;
		vpixvertical = Vector3fAdd(&vpixvertical, &ScreenDownInc);//all shifted down one maybe needs offset!
		// I think it is better performance adding an increment
		vpixhorizontal = Vector3fSub(&ScreenLeft, &ScreenRightInc);//resetting to left hand edge
		//(subtracting offset as well)
		
		while (counter_pixels < (self->image_width)){
			vpixhorizontal = Vector3fAdd(&vpixhorizontal, &ScreenRightInc);
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
	
	
	//printf("\n");
}


Pixel ScreenGetPixel(Screen* self, int x, int y){
	return self->pixel_array[y][x];
}

Vector3f ScreenGetPosition(Screen* self){
	return self->position;
}

float ScreenGetPixelWidth(Screen* self){
    return self->pixel_width;
}

int ScreenGetImageWidth(Screen* self){
	return self->image_width;
}

int ScreenGetImageHeight(Screen* self){
	return self->image_height;
}

Vector3f ScreenGetUpVec(Screen* self){
    return self->up;
}

Vector3f ScreenGetUpDir(Screen* self){
    return self->up_dir;
}

Vector3f ScreenGetLeftVec(Screen* self){
    return self->left;
}

Vector3f ScreenGetLeftDir(Screen* self){
    return self->left_dir;
}

Vector3f ScreenGetRightInc(Screen* self){
    return Vector3fMulF(&(self->left_dir), (-1 * self->pixel_width));
}

Vector3f ScreenGetDownInc(Screen* self){
    return Vector3fMulF(&(self->up_dir), (-1 * self->pixel_width));
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

Vector3f PixelGetPosition(Pixel* self){
	return self->position;
}





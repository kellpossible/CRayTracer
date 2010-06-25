#include <stdio.h>
#include "Colours.h"
#include "Vectors.h"

ColourRGB ColourRGBCreateDefault(void){
	ColourRGB c1;
	c1.rgb[0] = 0;
	c1.rgb[1] = 0;
	c1.rgb[2] = 0;
	return c1;
}

Vector3f ColourXYZCreateDefault(void){
	Vector3f c1;
	c1.xyz[0] = 1.0f;
	c1.xyz[1] = 1.0f;
	c1.xyz[2] = 1.0f;
	return c1;
}


ColourRGB ColourRGBAdd(const ColourRGB* c1, const ColourRGB* c2){
	ColourRGB c3;
	c3.rgb[0] = c1->rgb[0] + c2->rgb[0];
	c3.rgb[1] = c1->rgb[1] + c2->rgb[1];
	c3.rgb[2] = c1->rgb[2] + c2->rgb[2];
	return c3;
}

ColourRGB ColourRGBSub(const ColourRGB* c1, const ColourRGB* c2){
	ColourRGB c3;
	c3.rgb[0] = c1->rgb[0] - c2->rgb[0];
	c3.rgb[1] = c1->rgb[1] - c2->rgb[1];
	c3.rgb[2] = c1->rgb[2] - c2->rgb[2];
	return c3;
}


void ColourRGBPrint(const ColourRGB* c1){
	printf("r: %d, g: %d, b: %d\n", 
		c1->rgb[0],
		c1->rgb[1],
		c1->rgb[2]);
}
void Colour3fPrint(const Vector3f* v1){
	printf("r: %.3f, g: %.3f, b: %.3f\n", 
		v1->xyz[0],
		v1->xyz[1],
		v1->xyz[2]);
}


Vector3f ColourRGB2Vector3f(ColourRGB* c1){
	Vector3f v1;
	v1.xyz[0] = ((float)c1->rgb[0])/255.0f;
	v1.xyz[1] = ((float)c1->rgb[1])/255.0f;
	v1.xyz[2] = ((float)c1->rgb[2])/255.0f;
	return v1;
}
ColourRGB Vector3f2ColourRGB(Vector3f* v1){
	ColourRGB c1;
	int counter = 0;
	
	while (counter < 3){
		if (v1->xyz[counter] <= 1 ){
			if (v1->xyz[counter] >= 0){
				c1.rgb[counter] = (int)(v1->xyz[counter]) * 255;
			}
			else {
				c1.rgb[counter] = 0;
			}	
		}
		else {
			c1.rgb[counter] = 255;
		}
				
		counter += 1;
	}
	return c1;
}

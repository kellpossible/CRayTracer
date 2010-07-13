#include <stdio.h>
#include "Image.h"
#include "Colours.h"
int main(){
	int is = 10;
	Image* image = ImageCreate(is, is);
	
	int x, y;
	y = 0;
	while (y < is){
		x=0;
		if (y%2 == 1){
			x=0;
			while (x < is){
				ColourRGB col = {{0,0,0}};
				ImageWritePoint(image, col, x, y);
				x+=1;
			}
		}
		else{
			while (x < is){
				ColourRGB col = {{255,255,255}};
				ImageWritePoint(image, col,x, y);
				x+=1;
			}
		}
		y+=1;
	}
	
	ImageWriteFilePPM3(image, "TESTIMAGE.ppm");
	ImageFree(image);
	return 0;
}


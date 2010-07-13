#include <stdlib.h>
#include <stdio.h>
#include "Image.h"
#include "Colours.h"

#define MAXIMAGESIZE 10000
struct Image {
	int width;
	int height;
	int n_rows;
	int row_pos;
	ColourRGB pixel_rows[MAXIMAGESIZE][MAXIMAGESIZE];
	/* may need to change to pixel type*/
};

Image* ImageCreate(int width, int height){
	Image* self = malloc(sizeof(Image));
	self->width = width;
	self->height = height;
	ColourRGB colour_black = {{0, 0, 0}};
	
	int y = 0;
	int x;
	while (y < self->height){
		x=0;
		while (x < self->width){
			(self->pixel_rows)[y][x] = colour_black;
			x+=1;
		}
		y+=1;
	}
	
	
	self->n_rows = 0;
	self->row_pos = 0;
	return self;
}

void ImageFree(Image* self){
	free(self);
}

void ImageWritePoint(Image* self, ColourRGB col, int x, int y){
	self->pixel_rows[y][x] = col;
}

/*
void ImageWriteRow(Image* self, ColourRGB pixel_row[]){
	self->pixel_rows[self->row_pos] = pixel_row;
	self->row_pos += 1;
}
*/

int ImageGetWidth(Image* self){
	return self->width;
}

int ImageGetHeight(Image* self){
	return self->height;
}

void ImageWriteFilePPM3(Image* self, char* filename){
	FILE *file = fopen(filename, "w");
	ColourRGB col;
	fprintf(file, "P3\n");
	fprintf(file, "%d %d\n", self->width, self->height);
	fprintf(file, "255\n");
	
	int x, y;
	y = 0;
	while (y < self->height){
		x=0;
		while (x < self->width){
			col = self->pixel_rows[y][x];
			if (x == self->width - 1){
				fprintf(file, "%d %d %d\n", col.rgb[0], col.rgb[1], col.rgb[2]);
			}
			else{
				fprintf(file, "%d %d %d  ", col.rgb[0], col.rgb[1], col.rgb[2]);
			}
			x+=1;
		}
		y+=1;
	}
	fclose(file);
}

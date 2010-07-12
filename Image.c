#include <stdlib.h>
#include "Image.h"

#define MAXIMAGESIZE 10000
struct Image {
	int width;
	int height;
	Colour* pixel_rows[MAXIMAGESIZE];
	Colour pixel_row[MAXIMAGESIZE];
	/* may need to change to pixel type*/
};

Image* ImageCreate(int width, int height){
	Image* self = malloc(sizeof(Image));
	self->width = width;
	self->heigth = height;
}

#ifndef Image_h
#define Image_h
#include "Colours.h"

typedef struct Image Image;

Image* ImageCreate(int width, int height);
void ImageFree(Image* self);

void ImageWritePoint(Image* self, ColourRGB col, int x, int y);
void ImageWriteRow(Image* self, ColourRGB pixel_row[], int index);

int ImageGetWidth(Image* self);
int ImageGetHeight(Image* self);


void ImageWriteFilePPM3(Image* self, char* filename);




#endif

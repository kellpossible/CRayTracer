#ifndef Image_h
#define Image_h
#include "Colours.h"

typedef struct Image Image;

Image* ImageCreate(int width, int height);

void ImageWriteFile(char* filename);




#endif

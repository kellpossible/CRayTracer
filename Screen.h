#ifndef Screen_h
#define Screen_h
#include "View.h"

typedef struct Pixel Pixel;
typedef struct Screen Screen;


Screen* ScreenCreate(float width, int image_width, int image_height, View* view);
void ScreenFree(Screen*);

void ScreenPrint(Screen*);


#endif

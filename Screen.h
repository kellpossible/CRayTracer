#ifndef Screen_h
#define Screen_h
#include "Vectors.h"

struct Pixel {
	int x;
	int y;
	Vector3f position;
	Vector3f colour;
};

typedef struct Pixel Pixel;
typedef struct Screen Screen;


Screen* ScreenCreate(float width, int image_width, int image_height);
void ScreenCalibrate(Screen* self, Vector3f cam_pos, Vector3f view_vec);
void ScreenFree(Screen*);

Pixel ScreenGetPixel(Screen* self, int x, int y);
Vector3f ScreenGetPosition(Screen* self);
Vector3f PixelGetPosition(Pixel* self);

int ScreenGetImageWidth(Screen* self);
int ScreenGetImageHeight(Screen* self);

void ScreenPrint(Screen*);

/* private */
Pixel PixelCreate(int, int, Vector3f);


#endif

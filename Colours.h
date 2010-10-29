#ifndef Colours_h
#define Colours_h
#include "Vectors.h"

struct ColourRGB {
	int rgb[3];
};

typedef struct ColourRGB ColourRGB;
typedef struct Vector3f Colour3f;



ColourRGB ColourRGBAdd(const ColourRGB*, const ColourRGB*);
ColourRGB ColourRGBSub(const ColourRGB*, const ColourRGB*);
ColourRGB ColourRGBAverage4(ColourRGB*,ColourRGB*,ColourRGB*,ColourRGB*);
float ColourRGBDiff4(ColourRGB*,ColourRGB*,ColourRGB*,ColourRGB*); //TODO: Broken needs fixing
//currently printing out output as relative to the average of the pixels, which should
//not be the case.

void ColourRGBPrint(const ColourRGB*);
void Colour3fPrint(const Vector3f*);

Vector3f ColourRGB2Vector3f(ColourRGB*);
ColourRGB Vector3f2ColourRGB(Vector3f*);

ColourRGB ColourRGBCreateDefault(void);
ColourRGB ColourRGBCreate(int r, int g, int b);
Vector3f ColourXYZCreateDefault(void);

#endif

#include "ToneMap.h"
#include "Colours.h"
#include "Vectors.h"
#include <stdio.h>

ColourRGB ToneMapSimple(Vector3f vec_colour){
	return Vector3f2ColourRGB(&vec_colour);
}

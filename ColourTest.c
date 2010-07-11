#include <stdio.h>
#include "Colours.h"

/* expected output: */
/* r: 255, g: 10, b: 0 */

int main(){
	ColourRGB c1 = {{255, 10, 0}};
	ColourRGBPrint(&c1);
	return 0;
}

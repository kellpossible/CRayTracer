#include <stdio.h>
#include "Colours.h"
#include "Vectors.h"

ColourRGB ColourRGBCreateDefault(void){
	ColourRGB c1;
	c1.rgb[0] = 0;
	c1.rgb[1] = 0;
	c1.rgb[2] = 0;
	return c1;
}

ColourRGB ColourRGBCreate(int r, int g, int b){
	ColourRGB c1;
	c1.rgb[0] = 0;
	c1.rgb[1] = 0;
	c1.rgb[2] = 0;
	return c1;
}


Vector3f ColourXYZCreateDefault(void){
	Vector3f c1;
	c1.xyz[0] = 1.0f;
	c1.xyz[1] = 1.0f;
	c1.xyz[2] = 1.0f;
	return c1;
}


ColourRGB ColourRGBAdd(const ColourRGB* c1, const ColourRGB* c2){
	ColourRGB c3;
	c3.rgb[0] = c1->rgb[0] + c2->rgb[0];
	c3.rgb[1] = c1->rgb[1] + c2->rgb[1];
	c3.rgb[2] = c1->rgb[2] + c2->rgb[2];
	return c3;
}

ColourRGB ColourRGBSub(const ColourRGB* c1, const ColourRGB* c2){
	ColourRGB c3;
	c3.rgb[0] = c1->rgb[0] - c2->rgb[0];
	c3.rgb[1] = c1->rgb[1] - c2->rgb[1];
	c3.rgb[2] = c1->rgb[2] - c2->rgb[2];
	return c3;
}

ColourRGB ColourRGBAverage4(ColourRGB* c1,
                            ColourRGB* c2,
                            ColourRGB* c3,
                            ColourRGB* c4){
    ColourRGB* c_array[4] = {c1, c2, c3, c4};
    int r_sum = 0, b_sum = 0, g_sum = 0;
    int i=0;
    while (i < 3){
        r_sum += (*(c_array[i])).rgb[0];//false alarm in netbeans
        g_sum += (*(c_array[i])).rgb[1];
        b_sum += (*(c_array[i])).rgb[2];
        i++;
    }
    ColourRGB ret_col;
    ret_col.rgb[0] = ((float)r_sum)/3.0f;
    ret_col.rgb[1] = ((float)g_sum)/3.0f;
    ret_col.rgb[2] = ((float)b_sum)/3.0f;
    /*printf("C1: ");
    ColourRGBPrint(c1);
    printf("RETCOL: ");
    ColourRGBPrint(&ret_col);*/
    return ret_col;
}


float ColourRGBDiff4(//should convert to using an array for any number of colours
        ColourRGB* c1,
        ColourRGB* c2,
        ColourRGB* c3,
        ColourRGB* c4){
    float b_sum = 0.0f, b_diff_sum = 0.0f;
    float b, b_diff, b_av;
    float b_array[4];
    int i;
    ColourRGB* c_array[4] = {c1, c2, c3, c4};
    
    i=0;
    while (i < 3){
        //printf("colour %d", (*(c_array[i])).rgb[0]);
        b = ((float)((*(c_array[i])).rgb[0]//false alarm in netbeans
                   + (*(c_array[i])).rgb[1]
                   + (*(c_array[i])).rgb[2]))/(3.0f * 255.0f) ;
        b_sum += b;
        b_array[i] = b; //18382
        i++;
    }

    b_av = (b_sum)/(4.0f);

    i = 0;
    while (i < 3){
        b_diff = b_av - b_array[i];
        if (b_diff < 0.0f){
            b_diff *= -1;
        }
        b_diff_sum += b_diff;

        i++;
    }
    return b_diff_sum/4.0f; //b_diff_av

}


void ColourRGBPrint(const ColourRGB* c1){
	printf("r: %d, g: %d, b: %d\n", 
		c1->rgb[0],
		c1->rgb[1],
		c1->rgb[2]);
}
void Colour3fPrint(const Vector3f* v1){
	printf("r: %.3f, g: %.3f, b: %.3f\n", 
		v1->xyz[0],
		v1->xyz[1],
		v1->xyz[2]);
}


Vector3f ColourRGB2Vector3f(ColourRGB* c1){
	Vector3f v1;
	v1.xyz[0] = ((float)c1->rgb[0])/255.0f;
	v1.xyz[1] = ((float)c1->rgb[1])/255.0f;
	v1.xyz[2] = ((float)c1->rgb[2])/255.0f;
	return v1;
}
ColourRGB Vector3f2ColourRGB(Vector3f* v1){
	ColourRGB c1;
	int r, g, b;
	r = (int)((v1->xyz[0])*255.0f);
	if (r > 255)
	{
		r = 255;
	}
	else if (r < 0)
	{
		r = 0;
	}
	c1.rgb[0] = r;
	
	g = (int)((v1->xyz[1])*255.0f);
	if (g > 255)
	{
		g = 255;
	}
	else if (g < 0)
	{
		g = 0;
	}
	c1.rgb[1] = g;
	
	b = (int)((v1->xyz[2])*255.0f);
	if (b > 255)
	{
		b = 255;
	}
	else if (b < 0)
	{
		b = 0;
	}
	c1.rgb[2] = b;
	
	//ColourRGBPrint(&c1);
	return c1;
}

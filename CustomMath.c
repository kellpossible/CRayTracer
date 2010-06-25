#include "CustomMath.h"
#define BIGNUM 100000000


float fDiv(float f1, float f2){
	if (f2 == 0.0f){
		if (f1 == 0.0f){
			return 0.0f;
		}
		else {
			return (float)(BIGNUM * fSign(f1));
		}
	}
	else {
		if (f1 == 0.0f){
			return 0.0f;
		}
		else {
			if((f1 + f2) == f1){
				return (float)BIGNUM * (float)fSign(f1) * (float)fSign(f2);
			}
			else {
				return f1/f2;
			}
		}
	}
}

int fSign(float x){
	if (x == 0.0f){
		return 0;
	}
	else {
		if (x < 0.0f){
			return -1;
		}
		else {
			return 1;
		}
	}
}

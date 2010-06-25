#include <math.h>
#include <stdio.h>

#include "Vectors.h"
#include "CustomMath.h"

float Vector3fDot(const Vector3f* v1, const Vector3f* v2){
	return 	(v1->xyz[0] * v2->xyz[0]) +
		(v1->xyz[1] * v2->xyz[1]) +
		(v1->xyz[2] * v2->xyz[2]);
}

Vector3f Vector3fCross(const Vector3f* v1, const Vector3f* v2){
	Vector3f v3;
	v3.xyz[0] = (v1->xyz[1] * v2->xyz[2]) - (v1->xyz[2] * v2->xyz[1]);
	v3.xyz[1] = (v1->xyz[2] * v2->xyz[0]) - (v1->xyz[0] * v2->xyz[2]);
	v3.xyz[2] = (v1->xyz[0] * v2->xyz[1]) - (v1->xyz[1] * v2->xyz[0]);
	return v3;
}

Vector3f Vector3fSub(const Vector3f* v1, const Vector3f* v2){
	Vector3f v3;
	v3.xyz[0] = v1->xyz[0] - v2->xyz[0];
	v3.xyz[1] = v1->xyz[1] - v2->xyz[1];
	v3.xyz[2] = v1->xyz[2] - v2->xyz[2];
	return v3;
}

Vector3f Vector3fAdd(const Vector3f* v1, const Vector3f* v2){
	Vector3f v3;
	v3.xyz[0] = v1->xyz[0] + v2->xyz[0];
	v3.xyz[1] = v1->xyz[1] + v2->xyz[1];
	v3.xyz[2] = v1->xyz[2] + v2->xyz[2];
	return v3;
}

Vector3f Vector3fNeg(const Vector3f* v1){
	Vector3f v2;
	v2.xyz[0] = v1->xyz[0] * -1.0f;
	v2.xyz[1] = v1->xyz[0] * -1.0f;
	v2.xyz[2] = v1->xyz[0] * -1.0f;
	return v2;
}

Vector3f Vector3fMulV(const Vector3f* v1, const Vector3f* v2){
	Vector3f v3;
	v3.xyz[0] = v1->xyz[0] * v2->xyz[0];
	v3.xyz[1] = v1->xyz[1] * v2->xyz[1];
	v3.xyz[2] = v1->xyz[2] * v2->xyz[2];
	return v3;
}

Vector3f Vector3fMulF(const Vector3f* v1, float f1){
	Vector3f v3;
	v3.xyz[0] = v1->xyz[0] * f1;
	v3.xyz[1] = v1->xyz[1] * f1;
	v3.xyz[2] = v1->xyz[2] * f1;
	return v3;
}


Vector3f Vector3fDivF(const Vector3f* v1, float f1){
	Vector3f v2;
	v2.xyz[0] = fDiv(v1->xyz[0], f1);
	v2.xyz[1] = fDiv(v1->xyz[1], f1);
	v2.xyz[2] = fDiv(v1->xyz[2], f1);
	return v2;
}


Vector3f Vector3fNormalize(const Vector3f* v1){
	float v1_mag = (float)sqrt((float)Vector3fDot(v1, v1));
	Vector3f v2 = Vector3fDivF(v1, v1_mag);
	return v2;
}

float Vector3fMag(const Vector3f* v1){
	return (float)sqrt((float)Vector3fDot(v1, v1));
}

float Vector3fLen(const Vector3f* v1){
	return (float)sqrt((float)Vector3fDot(v1, v1));
}

void Vector3fPrint(const Vector3f* v1){
	printf("x: %.3f, y: %.3f, z: %.3f\n", 
		v1->xyz[0],
		v1->xyz[1],
		v1->xyz[2]);
}

/* constants */
const Vector3f Vector3fZERO = {{ 0.0f, 0.0f, 0.0f }};
const Vector3f Vector3fONE  = {{ 1.0f, 1.0f, 1.0f }};



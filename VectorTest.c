#include "Vectors.h"
#include <stdio.h>

int main(){
	const Vector3f v1 = {{1, 2, 3}};
	const Vector3f v2 = {{3, 0, 0}};
	Vector3f v3;
	float f1, f2;
	printf("\nv1\n");
	Vector3fPrint(&v1);
	
	printf("\nv2\n");
	Vector3fPrint(&v2);
	
	v3 = Vector3fAdd(&v1, &v2);
	printf("\nv1 + v2\n");
	Vector3fPrint(&v3);
	
	v3 = Vector3fSub(&v1, &v2);
	printf("\nv1 - v2\n");
	Vector3fPrint(&v3);
	
	v3 = Vector3fMulV(&v1, &v2);
	printf("\nv1 * v2\n");
	Vector3fPrint(&v3);
	
	v3 = Vector3fCross(&v1, &v2);
	printf("\ncross(v1, v2)\n");
	Vector3fPrint(&v3);
	
	f1 = Vector3fDot(&v1, &v2);
	printf("\ndot(v1, v2)\n");
	printf("float: %.3f\n", f1);
	
	f1 = Vector3fLen(&v2);
	printf("\nlen(v2)\n");
	printf("float: %.3f\n", f1);
	
	v3 = Vector3fMulF(&v1, 2.0f);
	printf("\nv1 * 2\n");
	Vector3fPrint(&v3);
}

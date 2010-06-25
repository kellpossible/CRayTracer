
#ifndef Vectors_h
#define Vectors_h

struct Vector3f {
	float xyz[3];
};

typedef struct Vector3f Vector3f;

float Vector3fDot(const Vector3f*, const Vector3f*);
Vector3f Vector3fCross(const Vector3f*, const Vector3f*);

Vector3f Vector3fAdd(const Vector3f*, const Vector3f*);
Vector3f Vector3fSub(const Vector3f*, const Vector3f*);

Vector3f Vector3fNeg(const Vector3f*);

Vector3f Vector3fMulV(const Vector3f*, const Vector3f*);
Vector3f Vector3fMulF(const Vector3f*, float);

Vector3f Vector3fDivF(const Vector3f*, float);

Vector3f Vector3fNormalize(const Vector3f*);
float Vector3fMag(const Vector3f*);
float Vector3fLen(const Vector3f*);

void Vector3fPrint(const Vector3f*);


/* constants */
extern const Vector3f Vector3fZERO;
extern const Vector3f Vector3fONE;

#endif

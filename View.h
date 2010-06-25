#ifndef View_h
#define View_h
#include "Vectors.h"

typedef struct View View;

View* ViewCreate(Vector3f* position, Vector3f* target_position, float focal_length);
void ViewFree(View*);

Vector3f ViewGetViewVector(View*);
Vector3f ViewGetDirection(View*);

float ViewGetFocalLength(View*);
Vector3f ViewGetTarget(View*);
Vector3f ViewGetPosition(View*);

void ViewPrint(View*);



#endif

#ifndef IntersectPoint_h
#define IntersectPoint_h

#include "Vectors.h"

typedef struct IntersectPoint IntersectPoint;


IntersectPoint* IntersectPointCreate(const Vector3f position, const Vector3f normal,int type);
/* 
if type = 0 then no intersection
if type = 1 then intersection from inside
if type = 2 then intersection from outiside
*/

IntersectPoint* IntersectPointCreateMiss(void);
void IntersectPointFree(IntersectPoint*);

Vector3f* IntersectPointGetPos(IntersectPoint*);
Vector3f IntersectPointGetNormal(IntersectPoint*);
int IntersectPointGetType(IntersectPoint*);
#endif

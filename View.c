#include <stdlib.h>
#include <stdio.h>

#include "View.h"
#include "Vectors.h"

struct View{
	Vector3f* position;
	Vector3f* target_position;
	float focal_length;
	Vector3f* view_vector;
	Vector3f* direction;
};

View* ViewCreate(Vector3f* position,
		 Vector3f* target_position,
		 float focal_length)
{
	Vector3f vv1, vv2;
	View* self = malloc(sizeof(View));
	Vector3f* view_vector = malloc(sizeof(Vector3f));
	Vector3f* direction = malloc(sizeof(Vector3f));
	
	self->position = position;
	self->target_position = target_position;
	self->focal_length = focal_length;
	
	vv1 = Vector3fSub(self->target_position, self->position);
	
	*direction = Vector3fNormalize(&vv1);
	self->direction = direction;
	
	*view_vector = Vector3fMulF(direction, self->focal_length);
	self->view_vector = view_vector;
	
	return self;
}

void ViewFree(View* self){
	free(self->view_vector);
	free(self->direction);
	free(self);
}

Vector3f ViewGetViewVector(View* self){
	return *(self->view_vector);
}

Vector3f ViewGetDirection(View* self){
	return *(self->direction);
}

float ViewGetFocalLength(View* self){
	return self->focal_length;
}

Vector3f ViewGetPosition(View* self){
	return *(self->position);
}

Vector3f ViewGetTarget(View* self){
	return *(self->target_position);
}

void ViewPrint(View* self){
	printf("\nView %i Stats: \n", (int)self);
	printf("Position: ");
	Vector3fPrint(self->position);
	printf("Target: ");
	Vector3fPrint(self->target_position);
	printf("Direction: ");
	Vector3fPrint(self->direction);
	printf("Focal Length: %.3f\n", self->focal_length);
	printf("View Vector: ");
	Vector3fPrint(self->view_vector);
}

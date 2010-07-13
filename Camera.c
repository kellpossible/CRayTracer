#include <stdlib.h>
#include <stdio.h>

#include "Camera.h"
#include "Vectors.h"
#include "Screen.h"

struct Camera{
	Screen* screen;
	Vector3f* position;
	Vector3f* target_position;
	float focal_length;
	Vector3f* view_vector;
	Vector3f* direction;
};

Camera* CameraCreate(Screen* screen,
		 Vector3f* position,
		 Vector3f* target_position,
		 float focal_length)
{
	Vector3f vv1, vv2;
	Camera* self = malloc(sizeof(Camera));
	self->screen = screen;
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
	
	ScreenCalibrate(screen, *position, *view_vector);
	
	return self;
}

void CameraFree(Camera* self){
	free(self->view_vector);
	free(self->direction);
	free(self);
}

Screen* CameraGetScreen(Camera* self){
	return self->screen;
}

Vector3f CameraGetViewVector(Camera* self){
	return *(self->view_vector);
}

Vector3f CameraGetDirection(Camera* self){
	return *(self->direction);
}

float CameraGetFocalLength(Camera* self){
	return self->focal_length;
}

Vector3f CameraGetPosition(Camera* self){
	return *(self->position);
}

Vector3f CameraGetTarget(Camera* self){
	return *(self->target_position);
}

void CameraPrint(Camera* self){
	printf("\nCamera %i Stats: \n", (int)self);
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

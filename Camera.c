#include "Camera.h"
#include <stdlib.h>
#include <stdio.h>
#include "View.h"
#include "Screen.h"
struct Camera {
	View* view;
	Screen* screen;
};

Camera* CameraCreate(View* view, Screen* screen){
	Camera* self = malloc(sizeof(Camera));
	self->view = view;
	self->screen = screen;
	return self;
}

void CameraFree(Camera* self){
	free(self);
}

View* CameraGetView(Camera* self){
	return self->view;
}

Screen* CameraGetScreen(Camera* self){
	return self->screen;
}


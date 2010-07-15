#ifndef Camera_h
#define Camera_h
#include "Vectors.h"
#include "Screen.h"

typedef struct Camera Camera;

Camera* CameraCreate(Screen* screen, Vector3f* position, Vector3f* target_position, float focal_length);
void CameraFree(Camera*);

Screen* CameraGetScreen(Camera* self);
Vector3f CameraGetViewVector(Camera*);
Vector3f CameraGetDirection(Camera*);

float CameraGetFocalLength(Camera*);
Vector3f CameraGetTarget(Camera*);
Vector3f CameraGetPosition(Camera*);

void CameraPrint(Camera*);



#endif

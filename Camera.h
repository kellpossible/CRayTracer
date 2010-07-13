#ifndef Camera_h
#define Camera_h
#include "Screen.h"
#include "View.h"
typedef struct Camera Camera;

Camera* CameraCreate(View*, Screen*);
void CameraFree(Camera*);

View* CameraGetView(Camera* self);
Screen* CameraGetScreen(Camera* self);


#endif

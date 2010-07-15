#ifndef Light_h
#define Light_h

typedef struct Light Light;

Light* LightCreate(char* name, Vector3f position, float power);
void LightFree(Light* self);

char* LightGetName(Light* self);
Vector3f LightGetPosition(Light* self);
float LightGetPower(Light* self);


#endif

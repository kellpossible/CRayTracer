#ifndef Sample_h
#define Sample_h
#include "Scene.h"
#include "Image.h"


Image* SampleSimple(Scene*);
ColourRGB SampleSuper1(   Scene* scene,
                    Vector3f* ray_vec,
                    Vector3f* pixel_origin,
                    float depth);
#endif /* Sample_h */

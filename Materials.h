#ifndef Materials_h
#define Materials_h
//why can't I move these structs elsewhere?
#include "Vectors.h"
#include "Colours.h"
#include "Lights.h"

typedef struct Material Material;
typedef struct MaterialType MaterialType;

Material* MaterialCreate(char* name, Vector3f colour);
Material* MaterialDefault(void);
void MaterialFree(Material* self);

Vector3f MaterialGetColour(Material* self);
char* MaterialGetName(Material* self);

Vector3f MaterialLambertDiffuse(Material* self, 
				Light* light,
				Vector3f light_dir,
				Vector3f normal);

#endif

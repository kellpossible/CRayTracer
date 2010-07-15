#include <stdlib.h>
#include "Materials.h"
#include "Vectors.h"

struct MaterialType {
};

struct Material {
	char* name;
	Vector3f colour;
};

Material* MaterialCreate(char* name, Vector3f colour){
	Material* self = malloc(sizeof(Material));
	self->name = name;
	self->colour = colour;
	return self;
}

Material* MaterialDefault(void){
	Vector3f col = {{0.8f, 0.8f, 0.8f}};
	return MaterialCreate("DefaultMaterial", col);
}

void MaterialFree(Material* self){
	free(self);
}


Vector3f MaterialGetColour(Material* self){
	return self->colour;
}

char* MaterialGetName(Material* self){
	return self->name;
}

Vector3f MaterialLambertDiffuse(Material* self, 
				Light* light,
				Vector3f light_dir,
				Vector3f normal){
	float shade = Vector3fDot(&light_dir, &normal);
	if (shade<0.0f)
	{
		shade=0.0f;
	}
	else if (shade > 1.0f)
	{
		shade=1.0f;
	}
	return Vector3fMulF(&(self->colour), shade);
}

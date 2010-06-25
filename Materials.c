#include <stdlib.h>
#include "Materials.h"

Material* MaterialDefault(void){
	Material* m = malloc(sizeof(Material));
	m->name = "DefaultMaterial";
	return m;
}

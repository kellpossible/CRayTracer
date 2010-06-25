#ifndef Materials_h
#define Materials_h
//why can't I move these structs elsewhere?
struct Material {
	char* name;
};

struct MaterialType {
};

typedef struct Material Material;
typedef struct MaterialType MaterialType;


Material* MaterialDefault(void);

#endif

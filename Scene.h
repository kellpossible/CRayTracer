#ifndef Scene_h
#define Scene_h
struct Scene {
	Primative* primative;
	View* camera;
	Screen* screen;
	
};

typedef struct Scene Scene;


//Scene* SceneCreate(Primative* prim1, View* camera1, Screen* screen1);

#endif

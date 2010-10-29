#include "Sample.h"
#include "RayTrace.h"
#include "Ray.h"
#include "Scene.h"
#include "Screen.h"
#include "Camera.h"
#include "Image.h"
#include "ToneMap.h"
#include "Colours.h"
#include "Random.h"

Image* SampleSimple(Scene* scene){
	Camera* camera = SceneGetCamera(scene);
	Screen* screen = CameraGetScreen(camera);
	Image* im = ImageCreate(ScreenGetImageWidth(screen),
				ScreenGetImageHeight(screen));
	ColourRGB colour;
	
	
	
	int y = 0;
	int x;
	int n;
	Vector3f ray_vec, ray_norm, ray_pos, cam_pos;
	Pixel curr_pix;
	
	cam_pos = CameraGetPosition(camera);
	
	while (y < ScreenGetImageHeight(screen)){
		x = 0;
		while (x < ScreenGetImageWidth(screen)){
			curr_pix = ScreenGetPixel(screen, x, y);
			ray_pos = PixelGetPosition(&curr_pix);
			ray_vec = Vector3fSub(&ray_pos, &cam_pos);
			ray_norm = Vector3fNormalize(&ray_vec);
			Ray* r = RayCreate(ray_pos, ray_norm);
			colour = ToneMapSimple(RayTrace(r, scene));
			ImageWritePoint(im, colour, x, y);		
			
			
			RayFree(r);
			x++;
		}
		y++;
	}
	return im;
	
}

Image* SampleAA(Scene* scene){
    RandomBuffer random_buffer;
    RandomSeed(1, &random_buffer); 
    
    Camera* camera = SceneGetCamera(scene);
	Screen* screen = CameraGetScreen(camera);
	Image* im = ImageCreate(ScreenGetImageWidth(screen),
				ScreenGetImageHeight(screen));
	ColourRGB colour;
	
	
	
	int y = 0;
	int x;
	int n;
	Vector3f ray_vec, ray_norm, ray_pos, cam_pos;
	Pixel curr_pix;
	
	cam_pos = CameraGetPosition(camera);
	
	while (y < ScreenGetImageHeight(screen)){
		x = 0;
		while (x < ScreenGetImageWidth(screen)){
			curr_pix = ScreenGetPixel(screen, x, y);
			ray_pos = PixelGetPosition(&curr_pix);
			ray_vec = Vector3fSub(&ray_pos, &cam_pos);
			ray_norm = Vector3fNormalize(&ray_vec);
			Ray* r = RayCreate(ray_pos, ray_norm);
			colour = ToneMapSimple(RayTrace(r, scene));
			ImageWritePoint(im, colour, x, y);		
			
			
			RayFree(r);
			x++;
		}
		y++;
	}
	return im;

}

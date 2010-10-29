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
#include <stdio.h>
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

                        //float d = ColourRGBDiff4(&colour, &colour, &colour, &colour);
                        //printf("number %f:", d);
                        //ColourRGB print_col = ColourRGBAverage4(&colour, &colour, &colour, &colour);
                        //ColourRGBPrint(&colour);
                        //colour = SampleSuper1(scene, &ray_vec, &ray_pos, 1);

                        

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

ColourRGB SampleSuper(Scene* scene, Vector3f* ray_vec, Vector3f* pixel_origin, float depth){
    ColourRGB c1, c2, c3, c4;
    Vector3f ray1_dir, ray2_dir, ray3_dir, ray4_dir;
    Vector3f ray_disp_y, ray_disp_x;
    Vector3f ray1_disp, ray2_disp, ray3_disp, ray4_disp;
    Vector3f ray1_vec, ray2_vec, ray3_vec, ray4_vec;
    Vector3f ray1_orig, ray2_orig, ray3_orig, ray4_orig;
    float diff;

    Ray* r1;Ray* r2;Ray* r3;Ray* r4;

    Camera* camera = SceneGetCamera(scene);
    Screen* screen = CameraGetScreen(camera);
    
    Vector3f right_inc = ScreenGetRightInc(screen);
    Vector3f down_inc = ScreenGetDownInc(screen);
    
    float pixel_width = ScreenGetPixelWidth(screen);
    
    //top left
    ray_disp_x = Vector3fMulF(&right_inc, (-1.0f * pixel_width)/2.0f);
    ray_disp_y = Vector3fMulF(&down_inc, (-1.0f * pixel_width)/2.0f);
    ray1_disp = Vector3fAdd(&ray_disp_x, &ray_disp_y);
    ray1_vec = Vector3fAdd(ray_vec, &ray1_disp);
    ray1_orig = Vector3fAdd(pixel_origin, &ray1_disp);
    
    //top right
    ray_disp_x = Vector3fMulF(&right_inc, (1.0f * pixel_width)/2.0f);
    ray_disp_y = Vector3fMulF(&down_inc, (-1.0f * pixel_width)/2.0f);
    ray2_disp = Vector3fAdd(&ray_disp_x, &ray_disp_y);
    ray2_vec = Vector3fAdd(ray_vec, &ray2_disp);
    ray2_orig = Vector3fAdd(pixel_origin, &ray2_disp);

    //bottom left
    ray_disp_x = Vector3fMulF(&right_inc, (-1.0f * pixel_width)/2.0f);
    ray_disp_y = Vector3fMulF(&down_inc, (1.0f * pixel_width)/2.0f);
    ray3_disp = Vector3fAdd(&ray_disp_x, &ray_disp_y);
    ray3_vec = Vector3fAdd(ray_vec, &ray3_disp);
    ray3_orig = Vector3fAdd(pixel_origin, &ray3_disp);

    //bottom right
    ray_disp_x = Vector3fMulF(&right_inc, (1.0f * pixel_width)/2.0f);
    ray_disp_y = Vector3fMulF(&down_inc, (1.0f * pixel_width)/2.0f);
    ray4_disp = Vector3fAdd(&ray_disp_x, &ray_disp_y);
    ray4_vec = Vector3fAdd(ray_vec, &ray4_disp);
    ray4_orig = Vector3fAdd(pixel_origin, &ray4_disp);

    
    r1 = RayCreate(ray1_orig, Vector3fNormalize(&ray1_vec));
    r2 = RayCreate(ray1_orig, Vector3fNormalize(&ray2_vec));
    r3 = RayCreate(ray1_orig, Vector3fNormalize(&ray3_vec));
    r4 = RayCreate(ray1_orig, Vector3fNormalize(&ray4_vec));

    
    c1 = ToneMapSimple(RayTrace(r1, scene));
    c2 = ToneMapSimple(RayTrace(r2, scene));
    c3 = ToneMapSimple(RayTrace(r3, scene));
    c4 = ToneMapSimple(RayTrace(r4, scene));
    
    /*
    diff = ColourRGBDiff4(&c1, &c2, &c3, &c4);


    ColourRGBPrint(&c1);
    ColourRGBPrint(&c2);
    ColourRGBPrint(&c3);
    ColourRGBPrint(&c4);
    printf("%f\n", diff);
    printf("ColourAverage: ");
     */
    ColourRGB av = ColourRGBAverage4(&c1, &c2, &c3, &c4);
    //ColourRGBPrint(&av);
    return av;
}
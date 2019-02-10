#pragma once
#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include "common_function.h"
#define M_PI 3.14159
class Camera
{
public:
	//Camera(float vfov,float aspect,Vector look_to) {//aspect = nx/ny
	//	canvas_z = (look_to - origin).Length();
	//	pitch_theta =M_PI/2-atan(look_to.z/origin.y);
	//	//pitch_theta = pitch * M_PI / 180;
	//	float theta = vfov * M_PI / 180; 
	//	float half_height = abs(canvas_z)*tan(theta / 2.0);
	//	float half_width = aspect * half_height;
	//	low_left_corner = Vector(-half_width, -half_height, canvas_z);
	//	horizontal= Vector(2*half_width, 0, 0);
	//	vertical = Vector(0, 2*half_height, 0);
	//	origin = Vector(0, 10, 0);
	//}

	//Vector low_left_corner;
	//Vector horizontal;
	//Vector vertical;
	//Vector origin;
	//float canvas_z;
	//float pitch_theta;

	//Ray getRay(float u, float v) {
	//	float s = u;
	//	
	//	Vector dir = low_left_corner + horizontal * u + vertical * v;
	//	Vector dir_after = Vector(dir.x, cos(pitch_theta)*dir.y, canvas_z - dir.y * sin(pitch_theta));
	//	return Ray(origin, dir_after - origin);
	//}
	Camera(Vector lookfrom, Vector lookat, Vector vup, float vfov, float aspect,float aperture_,float dist_to_focus) { // vfov is top to bottom in degrees
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2)*dist_to_focus;
		float half_width = aspect * half_height;
		origin = lookfrom;
		aperture = aperture_;
		w = (lookfrom - lookat).normalize();
		u = vup.cross( w).normalize();
		v = w.cross( u);
		lower_left_corner = origin -  u* half_width  -  v*half_height  - w*dist_to_focus;
		horizontal = u*2 * half_width;
		vertical = v *2 * half_height;
	}
	Ray getRay(float s, float t) { 
		Vector rd =  random_unit_direction()*aperture;
		Vector offset = u*rd.x +v *rd.y;
		return Ray(origin+offset, lower_left_corner +  horizontal*s + vertical*t - (origin +offset));
	
	}
	Vector u, v, w;
	Vector lower_left_corner;
	Vector horizontal;
	Vector vertical;
	Vector origin;
	float aperture;

};


#endif // !CAMERAH

#pragma once
#ifndef SPHEREH
#define SPHEREH


#include "material.h"
#include "vector.h"
#include "ray.h"
#include "hitable.h"
class Sphere:public hitable  
{
public :
	float radius;
	Vector center;
	Material *mat_ptr;
	Sphere(const Vector &c, float r, Material *m) :radius(r), center(c), mat_ptr(m) {};
	
	virtual bool hit( Ray &r, float t_min, float t_max, hit_record& rec)const ;

	//bool hit_sphere(Ray r, Vector center, float radius);

	

};


#endif // !SPHEREH

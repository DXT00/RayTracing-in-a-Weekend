#pragma once
#ifndef MATERIALH
#define MATERIALH


#include "common_function.h"
#include"hitable.h"

#include<random>

class Material
{
public:
	Material() {};
	virtual bool scatter(Ray &r_in,hit_record &rec, Vector& attenuation, Ray& scattered)const = 0;

};

class lambertain:public Material
{
public:
	lambertain(const Vector&a) :albedo(a) {};
	virtual bool scatter(Ray &r_in, hit_record &rec, Vector& attenuation, Ray& scattered)const;

	Vector albedo;
};
class mental:public Material
{
public:
	mental(const Vector&a, float f) :albedo(a) { fuzzy = (f < 1) ? f : 1; }
	virtual bool scatter(Ray &r_in, hit_record& rec, Vector& attenuation, Ray& scattered)const;
	Vector albedo;
	float fuzzy;
};

class dielectrics:public Material
{
public:
	dielectrics(float ref):ref_idx(ref){}
	virtual bool scatter(Ray &r_in, hit_record& rec, Vector& attenuation, Ray& scattered)const;
	virtual bool refract(Ray & r_in,  Vector & rec_normal_, float nin_to_nout, Vector & refracted) const;


	float ref_idx;
};


#endif // !MATERIALH
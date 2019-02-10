#pragma once
#ifndef HITABLEH
#define HITABLEH
#include "vector.h"
#include "ray.h"
class Material;
struct hit_record {
	float t;
	Vector p;//hit point vector
	Vector normal;//∑®œÚ¡ø
	Material *material;
};

class hitable
{
public:
	virtual bool hit( Ray &r, float t_min, float t_max, hit_record& rec)const = 0;
};

#endif // !HITABLEH


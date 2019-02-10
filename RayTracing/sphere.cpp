#include"sphere.h" 
#include "ray.h"
#include "vector.h"

bool Sphere::hit( Ray & r, float t_min, float t_max, hit_record& rec) const
{
	Vector oc = r.origin - center;
	float a = r.direction.dot(r.direction);
	float b = 2 * oc.dot(r.direction);
	float c = oc.dot(oc) - radius * radius;
	float delta = b * b - 4 * a*c;
	rec.material = mat_ptr;
	if (delta <= 0)
		return false;
	
	float temp = (-b - sqrt(delta)) /(2.0*a);
	if (temp < t_max && temp > t_min) {
		rec.t = temp;
		rec.p = r.getPoint(rec.t);
		rec.normal = (rec.p - center)/ radius;
		return true;
	}
	temp = (-b + sqrt(delta)) / (2.0*a);
	if (temp < t_max && temp > t_min) {
		rec.t = temp;
		rec.p = r.getPoint(rec.t);
		rec.normal = (rec.p - center)/radius;
		return true;
	}

	return false;
}

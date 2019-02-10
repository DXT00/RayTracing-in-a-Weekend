#pragma once

#ifndef VECTORH
#define VECTORH


#include<math.h>
class Vector
{
public:
	float x, y, z;
	Vector(){}
	Vector(float x, float y, float z) :x(x), y(y), z(z) {}
	Vector(const Vector &r) :x(r.x), y(r.y), z(r.z) {}
	//~Vector();

	float sqrLength () const {
		return x*x + y*y + z*z;
	}
	float Length() const {
		return sqrt(sqrLength());
	}
	Vector operator-() const {
		return Vector(-x, -y, -z);
	}
	Vector operator+( Vector r) {
		return Vector(x + r.x, y + r.y, z + r.z);
	}
	Vector operator-(const Vector &r) {
		return Vector(x - r.x, y - r.y, z - r.z);
	}
	Vector operator*( Vector &r) {
		return Vector(x * r.x, y * r.y, z * r.z);
	}
	Vector operator*(float v) {
		return Vector(x*v, y*v, z*v);
	}
	Vector operator/(float v)const {
		return Vector(x / v, y / v, z / v);
	}
	Vector normalize()const {
		float  invlen = 1 / Length();
		return Vector(x*invlen, y*invlen, z*invlen);
	}
	float dot(const Vector &r)const {
		return x * r.x + y * r.y + z * r.z;
	}
	Vector cross(const Vector &r)const {
		return Vector(-z * r.y + y * r.z,
			z * r.x - x * r.z,
			-y * r.x + x * r.y);
	}
	static Vector zero() {
		return Vector(0, 0, 0);
	}

private:

};


#endif // !VECTORH
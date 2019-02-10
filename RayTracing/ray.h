#pragma once
#ifndef RAYH
#define RAYH


#include"vector.h"

class Ray
{
public:
	Vector origin;
	Vector direction;
	Ray() {};
	Ray(Vector o, Vector d){ origin = o; direction = d; }
	
	Vector getPoint(float t)  {
		Vector point = origin + direction*t;
		return point;
	}
	//Vector direction() const{
	//	return direction;
	//}
	//Vector origin()const {
	//	return origin;
	//}
		




	
};



#endif // !RAYH
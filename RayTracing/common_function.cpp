#include"common_function.h"
#include"vector.h"
Vector random_unit_direction() {
	Vector r;
	do
	{
		r = Vector(rand() % 100 / (float)100, rand() % 100 / (float)100, rand() % 100 / (float)100)*2.0 - Vector(1, 1, 1);
	} while (r.Length() >= 1.0);
	return r;
}
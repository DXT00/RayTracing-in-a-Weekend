#pragma once
#ifndef HITABLE_LISTH
#define HITABLE_LISTH


#include"hitable.h"


class hitable_list:public hitable
{
public:
	hitable_list(){}
	hitable_list(hitable **list,int n):list(list),list_size(n){}
	hitable **list;
	int list_size;
	virtual bool hit(Ray &r, float t_min, float t_max, hit_record& rec)const;


};
#endif // !HITABLE_LISTH
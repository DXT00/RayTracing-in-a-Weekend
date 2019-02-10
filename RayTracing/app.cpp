//#include "vector.h"

#include<iostream>
#include<fstream>
#include<iomanip>
#include<random>

#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include <float.h>
#define MAXFLOAT 3.402823466e+38F
using namespace std;
float hit_sphere(Ray r, Vector center, float radius) {
	Vector oc = r.origin - center;
	float a = r.direction.dot(r.direction);
	float b = 2 * oc.dot(r.direction);
	float c = oc.dot(oc) - radius * radius;
	float delta = b * b - 4 * a*c;
	if (delta < 0)
		return -1;
	else
		return (-b - sqrt(delta))/(2.0*a);
}


Vector color( Ray r,hitable_list *hit_list,int time) {
	//if hit
	//hitable_list hit_list;
	hit_record hit_rec;
	float t;
	if (hit_list->hit(r, 0.00001, MAXFLOAT, hit_rec)) {
		t = hit_rec.t;
		Material *mater = hit_rec.material;

		Ray reflect_ray;// = Ray(OP, reflect);
		Vector attenuation;
		if(time<50&&mater->scatter(r,hit_rec,attenuation,reflect_ray))
			return color(reflect_ray, hit_list,time+1)*attenuation;
		else {
			return Vector(0, 0, 0);
		}
	}
	else {
		//Draw background
		Vector unit_direction = r.direction.normalize();
		float t_ = 0.5*(unit_direction.y + 1.0);
		return Vector(1, 1, 1)*(1 - t_) + Vector(0.5, 0.7, 1)*t_;
	}
}

int main() {
	ofstream ofile("c:\\Users\\DXT00\\Desktop\\Graphics\\RayTracing\\ppm.txt");
	//ofile.open

	srand(time(0));
	int nx = 400;
	int ny = 200;
	int ns = 100;//边界模糊，随机采样100次
	ofile << "P3\n" << nx << " " << ny << "\n255\n";
	Vector lookfrom(-2, 2, 1);
	Vector lookto(0, 0, -1);
	float dist_to_focus = (lookfrom - lookto).Length();
	float aperture = 0.5;
	Camera camera(lookfrom, lookto, Vector(0, 1, 0), 50, float(nx) / float(ny),aperture,dist_to_focus);
	hitable *list[4];
	
	Material *m1 = new lambertain(Vector(0.1, 0.2, 0.5));
	Material *m2 = new lambertain(Vector(0.8, 0.8, 0.0));
	Material *m3 = new mental(Vector(0.8, 0.6, 0.2), 0.0);
	Material *m4 = new dielectrics(1.5);

	/*list[0] = new Sphere(Vector(0, 0, -1), 0.5, m1);
	list[1] = new Sphere(Vector(1, 0, -1), 0.5, m3);
	list[2] = new Sphere(Vector(0, -100.5, -1), 100, m2);
	list[3] = new Sphere(Vector(-0.7, 0, -1), 0.2, m4);*/
	list[0] = new Sphere(Vector(0, 0, -1), 0.5, m1 );
	list[1] = new Sphere(Vector(0, -100.5, -1), 100,m2);
	list[2] = new Sphere(Vector(1, 0, -1), 0.5, m3);
	list[3] = new Sphere(Vector(-1, 0, -1), 0.5,m4);
	
	hitable_list *hit_list=new hitable_list(list, 4);
	
	for (int j = ny-1; j>=0;j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Vector col(0,0,0);
			for (int k = 0; k < ns; k++)
			{
				float u = float(i+ rand() % 100 / (float)101) / float(nx);
				float v = float(j+ rand() % 100 / (float)101) / float(ny);
				Ray r = camera.getRay(u, v);
				 col=col+ color(r, hit_list,0);
			}
			col = col / float(ns);

			//gamma校正，让颜色不那么黑
			col = Vector(sqrt(col.x), sqrt(col.y), sqrt(col.z));
		
			
			int ir = (int(255.99*col.x));
			int ig = (int(255.99*col.y));
			int ib = (int(255.99*col.z));

		
			ofile << ir << " " << ig << " " << ib << endl;
		}
		
	}
	ofile.close();
}
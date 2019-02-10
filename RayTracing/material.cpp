#include "ray.h"
#include "material.h"

Vector reflect( Vector& v,  Vector& n) {
	/*获取镜面反射的反射光线的方向向量。具体计算，后面解释*/
	Vector vp;
	return v - n * 2.0 * v.dot(n);
}

bool lambertain::scatter(Ray &r_in, hit_record &rec, Vector& attenuation, Ray& scattered)const {
	Vector target = rec.p + rec.normal + random_unit_direction();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = albedo;
	return true;
}

 bool mental::scatter(Ray &r_in, hit_record& rec, Vector& attenuation, Ray& scattered)const {
	Vector unit_r_direction = r_in.direction.normalize();
	Vector target = unit_r_direction - rec.normal*2.0*(unit_r_direction.dot(rec.normal));
	scattered = Ray(rec.p, target+random_unit_direction()*fuzzy);
	attenuation = albedo;
	return(scattered.direction.dot(rec.normal) > 0);//保证反射vector和法向量间的角度<90度
}



 bool dielectrics::refract(Ray & r_in, Vector & rec_normal_,float nin_to_nout, Vector & refracted) const
 {
	 Vector I = r_in.direction.normalize();
	 float cos_a1 = -(I.dot(rec_normal_)) ;

	 float discriminant = 1.0 - (1 - cos_a1 * cos_a1)*nin_to_nout*nin_to_nout;
	 if (discriminant > 0) {
		  refracted = I * nin_to_nout + rec_normal_ *(nin_to_nout*cos_a1 - sqrt(discriminant));
		 //=(I+rec_normal_*cos_a1)*nin_to_nout  -rec_normal_*sqrt(discriminant)
		 return true;
	 }
	 else
		 return false;

 }

 bool dielectrics::scatter(Ray & r_in, hit_record & rec, Vector & attenuation, Ray & scattered) const
 {
	 attenuation = Vector(1.0, 1.0, 1.0);
	 Vector reflected = reflect(r_in.direction, rec.normal);
	 float nin_to_nout;// = (rec.normal.dot(r_in.direction) <= 0) ? 1.0 / ref_idx : ref_idx;
	 Vector normal_; //=  <= 0) ? rec.normal : -rec.normal;
	 
	 if (rec.normal.dot(r_in.direction) > 0){
		 nin_to_nout=ref_idx;
			 normal_ = -rec.normal;
	 }
	 else {
		 nin_to_nout = 1.0/ref_idx;
		 normal_ = rec.normal;
	 }
	 
	 Vector refracted;
	 if (refract(r_in, normal_, nin_to_nout, refracted)) {
		 scattered = Ray(rec.p, refracted);
		 
	 }
	 else {
		 scattered = Ray(rec.p, reflected);
		 return false;
	 }
	 
	return true;
 }



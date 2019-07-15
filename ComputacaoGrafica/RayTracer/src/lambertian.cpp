#include "lambertian.h"
#include "sphere.h"

// Definindo o construtor da classe
Lambertian::Lambertian(const Vec3& albedo)
: albedo(albedo) {}

// Definindo o destrutor da classe
Lambertian::~Lambertian() {}

// Métodos getter
Vec3 Lambertian::get_albedo() const {
    return this->albedo; 
}

// Definindo métodos da herança
bool Lambertian::scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
    Vec3 target = rec.point + rec.normal + Sphere::random_point();
    
    scattered = Ray(rec.point, target - rec.point);
    attenuation = this->albedo;
    return true;
}
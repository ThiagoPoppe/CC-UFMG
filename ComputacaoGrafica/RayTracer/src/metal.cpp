#include "metal.h"
#include "sphere.h"

// Definindo método que reflete um raio em torno da normal
Vec3 Metal::reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * Vec3::dot(v, n) * n;
}

// Definindo o construtor da classe
Metal::Metal(const Vec3& albedo, const float fuzz)
: albedo(albedo) {
    if (fuzz < 1)
        this->fuzz = fuzz;
    else
        this->fuzz = 1;
}

// Definindo o destrutor da classe
Metal::~Metal() {}

// Métodos getter
Vec3 Metal::get_albedo() const {
    return this->albedo;
}

float Metal::get_fuzz() const {
    return this->fuzz;
}

// Definindo métodos da herança
bool Metal::scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
    Vec3 reflected = reflect(Vec3::normalize(ray.get_dir()), rec.normal);

    scattered = Ray(rec.point, reflected + fuzz * Sphere::random_point());
    attenuation = this->albedo;
    return Vec3::dot(scattered.get_dir(), rec.normal) > 0;
}
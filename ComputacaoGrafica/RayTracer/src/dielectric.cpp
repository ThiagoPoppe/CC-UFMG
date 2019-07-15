#include <cmath>

#include "metal.h"
#include "dielectric.h"

// Definindo método para refratar um raio
bool Dielectric::refract(const Vec3& v, const Vec3& n, const float ref_idx, Vec3& refracted) const {
    Vec3 unit_vec = Vec3::normalize(v);

    float dt = Vec3::dot(unit_vec, n);
    float discriminant = 1 - ref_idx * ref_idx * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ref_idx * (unit_vec - n * dt) - n * sqrt(discriminant);
        return true;
    }

    return false;
}

// Definindo método para o cálculo do polinômio de Schlick
float Dielectric::schlick(const float cosine, const float ref_idx) const {
    float r0 = (float) (1 - ref_idx) / (1 + ref_idx);
    r0 *= r0;

    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

// Definindo o construtor da classe
Dielectric::Dielectric(const float ref_index)
: ref_index(ref_index) {}

// Definindo o destrutor da classe
Dielectric::~Dielectric() {}

// Métodos getter
float Dielectric::get_ref_index() const {
    return this->ref_index;
}

// Definindo métodos da herança
bool Dielectric::scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
    Vec3 normal;
    Vec3 refracted;
    float ref_idx;
    float cosine;
    float prob;

    Vec3 reflected = Metal::reflect(ray.get_dir(), rec.normal);
    attenuation = Vec3(1, 1, 1);

    if (Vec3::dot(ray.get_dir(), rec.normal) > 0) {
        normal = -rec.normal;
        ref_idx = this->ref_index;
        cosine = (float) ref_idx * Vec3::dot(ray.get_dir(), rec.normal) / ray.get_dir().norm();
    }
    else {
        normal = rec.normal;
        ref_idx = (float) 1 / this->ref_index;
        cosine = -Vec3::dot(ray.get_dir(), rec.normal) / ray.get_dir().norm();
    }

    if (refract(ray.get_dir(), normal, ref_idx, refracted))
        prob = schlick(cosine, ref_idx);
    else
        prob = 1;

    if (drand48() < prob)
        scattered = Ray(rec.point, reflected);
    else
        scattered = Ray(rec.point, refracted);

    return true;
}
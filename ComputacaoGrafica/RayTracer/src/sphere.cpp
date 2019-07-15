#include <cmath>

#include "sphere.h"

// Definindo o construtor da classe
Sphere::Sphere(Vec3 center, float radius, Material* material)
: center(center), radius(radius), material(material) {}

// Definindo o destrutor da classe
Sphere::~Sphere() {}

// Métodos getter
Vec3 Sphere::get_center() const {
    return this->center;
}

float Sphere::get_radius() const {
    return this->radius;
}

Material* Sphere::get_material() const {
    return this->material;
}

// Método que retorna um ponto aleatório em uma esfera unitária
Vec3 Sphere::random_point() {
    float r = sqrt(drand48());
    float t = 2 * M_PI * drand48();

    float x = r * cos(t);
    float y = r * sin(t);
    float z = drand48();

    return Vec3(x, y, z);
}

// Definindo o método hit
bool Sphere::hit(const Ray& ray, float t_min, float t_max, struct HitRecord& rec) const {
    // Computando o vetor entre a origem do raio e o centro da esfera
    Vec3 oc = ray.get_origin() - this->center;

    // Computando os coeficientes da nossa equação de segundo grau
    float a = Vec3::dot(ray.get_dir(), ray.get_dir());
    float b = Vec3::dot(oc, ray.get_dir());
    float c = Vec3::dot(oc, oc) - this->radius * this->radius;

    // Computando o discriminante e os casos de hit
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float aux = (-b - sqrt(discriminant)) / a;
        if (aux < t_max && aux > t_min) {
            rec.t = aux;
            rec.point = ray.point(aux);
            rec.normal = (rec.point - this->center) / this->radius;
            rec.mat = this->material;
            return true;
        }

        aux = (-b + sqrt(discriminant)) / a;
        if (aux < t_max && aux > t_min) {
            rec.t = aux;
            rec.point = ray.point(aux);
            rec.normal = (rec.point - this->center) / this->radius;
            rec.mat = this->material;
            return true;
        }
    }

    return false;
}
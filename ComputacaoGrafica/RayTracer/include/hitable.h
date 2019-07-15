#ifndef HITABLE_H
#define HITABLE_H

#include "vec3.h"
#include "ray.h"
#include "material.h"

// Declarando a classe Material por conta do compilador
class Material;

// Definindo uma struct para guardar os dados do hit
struct HitRecord {
    float t;
    Vec3 point;
    Vec3 normal;
    Material* mat;
};

// Definindo a classe abstrata Hitable
class Hitable {
    public:
        // Construtor e destrutor
        Hitable();
        virtual ~Hitable();

        // Método virtual para o hit de objetos
        virtual bool hit(const Ray& ray, float t_min, float t_max, struct HitRecord& rec) const = 0;
};

#endif
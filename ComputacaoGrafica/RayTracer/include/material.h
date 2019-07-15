#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"

// Declarando a struct HitRecord por conta do compilador
struct HitRecord;

class Material {
    public:
        // Construtor e destrutor
        Material();
        virtual ~Material();

        // Método que faz o scatter de um raio
        virtual bool scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

#endif
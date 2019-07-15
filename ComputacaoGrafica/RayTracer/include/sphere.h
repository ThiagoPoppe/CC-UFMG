#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"

class Sphere : public Hitable {
    // Definindo os atributos da classe
    private:
        Vec3 center;
        float radius;
        Material* material;

    public:
        // Construtor e destrutor
        Sphere(Vec3 center, float radius, Material* material);
        ~Sphere();

        // Métodos getter
        Vec3 get_center() const;
        float get_radius() const;
        Material* get_material() const;

        // Métodos static
        static Vec3 random_point();

        // Definindo métodos da herança
        virtual bool hit(const Ray& ray, float t_min, float t_max, struct HitRecord& rec) const;
};

#endif
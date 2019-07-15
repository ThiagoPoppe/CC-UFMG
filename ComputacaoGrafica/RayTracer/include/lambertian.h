#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material {
    // Definindo os atributos da classe
    private:
        Vec3 albedo;

    public:
        // Construtor e destrutor
        Lambertian(const Vec3& albedo);
        ~Lambertian();

        // Métodos getter
        Vec3 get_albedo() const;

        // Definindo métodos da herança
        virtual bool scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;
};

#endif
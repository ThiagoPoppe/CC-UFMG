#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

class Dielectric : public Material {
    // Definindo os atributos da classe
    private:
        float ref_index;

    // Definindo métodos privados
    private:
        bool refract(const Vec3& v, const Vec3& n, const float ref_idx, Vec3& refracted) const;
        float schlick(const float cosine, const float ref_idx) const;

    public:
        // Construtor e destrutor
        Dielectric(const float ref_index);
        ~Dielectric();

        // Métodos getter
        float get_ref_index() const;

        // Definindo métodos da herança
        virtual bool scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;
};

#endif
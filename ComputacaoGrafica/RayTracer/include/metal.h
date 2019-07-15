#ifndef METAL_H
#define METAL_H

#include "material.h"

class Metal : public Material {
    // Definindo os atributos da classe
    private:
        Vec3 albedo;
        float fuzz;

    public:
        // Construtor e destrutor
        Metal(const Vec3& albedo, const float fuzz);
        ~Metal();

        // Métodos getter
        Vec3 get_albedo() const;
        float get_fuzz() const;

        // Métodos da classe
        static Vec3 reflect(const Vec3& v, const Vec3& n);

        // Definindo métodos da herança
        virtual bool scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;
};

#endif
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    // Definindo os atributos da classe
    private:
        Vec3 origin;
        Vec3 dir;

    public:
        // Construtor e destrutor
        Ray();
        Ray(Vec3 origin, Vec3 dir);
        ~Ray();

        // Métodos getter
        Vec3 get_origin() const;
        Vec3 get_dir() const;

        // Métodos da classe
        Vec3 point(const float t) const;
};

#endif
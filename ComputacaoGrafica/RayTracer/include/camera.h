#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera {
    // Definindo os atributos da classe
    private:
        Vec3 origin, horizontal, vertical, lower_left_corner;

    public:
        // Construtor e destrutor
        Camera();
        ~Camera();

        // Métodos da classe
        Ray shoot_ray(const float s, const float t) const;
};

#endif
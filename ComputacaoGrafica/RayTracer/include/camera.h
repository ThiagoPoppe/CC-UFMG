#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera {
    // Definindo os atributos da classe
    private:
        Vec3 origin, horizontal, vertical, lower_left_corner;
        Vec3 u, v, w;
        float len_radius;

    // Definindo métodos privados da classe
    private:
        Vec3 random_in_unit_disk() const;

    public:
        // Construtor e destrutor
        Camera(const Vec3& origin, const Vec3& look_at, const Vec3& vup, const float fov,
               const float aspect, const float aperture, const float focus_dist);
        ~Camera();

        // Métodos da classe
        Ray shoot_ray(const float s, const float t) const;
};

#endif
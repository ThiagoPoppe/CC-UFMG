#include <cmath>

#include "camera.h"

// Definindo o construtor da classe
Camera::Camera() {
    this->lower_left_corner = Vec3(-2, -1, -1);
    this->horizontal = Vec3(4, 0, 0);
    this->vertical = Vec3(0, 2, 0);
    this->origin = Vec3(0, 0, 0);
}

// Definindo o destrutor da classe
Camera::~Camera() {}

// Definindo o método que dispara raios
Ray Camera::shoot_ray(const float s, const float t) const {
    Vec3 dir = this->lower_left_corner + s * this->horizontal + t * this->vertical - this->origin;
    return Ray(this->origin, dir);
}
#include "ray.h"

// Definindo o construtor da classe
Ray::Ray() {}

Ray::Ray(Vec3 origin, Vec3 dir) 
: origin(origin), dir(dir) {}

// Definindo o destrutor da classe
Ray::~Ray() {}

// Métodos getter
Vec3 Ray::get_origin() const {
    return this->origin;
}

Vec3 Ray::get_dir() const {
    return this->dir;
}

Vec3 Ray::point(const float t) const {
    return this->origin + this->dir * t;
}
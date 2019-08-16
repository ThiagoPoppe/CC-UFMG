#include "camera.h"

// Definindo o construtor da classe
Camera::Camera(const Vec3& origin, const Vec3& look_at, const Vec3& vup, const float fov,
               const float aspect, const float aperture, const float focus_dist) {

    float theta = fov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;

    this->w = Vec3::normalize(origin - look_at);
    this->u = Vec3::normalize(Vec3::cross(vup, w));
    this->v = Vec3::cross(w, u);

    this->len_radius = aperture / 2;
    this->lower_left_corner = origin - focus_dist * (half_width * u + half_height * v + w);
    this->horizontal = 2 * half_width * focus_dist * u;
    this->vertical = 2 * half_height * focus_dist * v;
    this->origin = origin;
}

// Definindo o destrutor da classe
Camera::~Camera() {}

// Definindo método que retorna um ponto aleatório em um círculo unitário
Vec3 Camera::random_in_unit_disk() const {
    float r = sqrt(drand48());
    float t = 2 * M_PI * drand48();

    float x = r * cos(t);
    float y = r * sin(t);

    return Vec3(x, y, 0);
}

// Definindo o método que dispara raios
Ray Camera::shoot_ray(const float s, const float t) const {
    Vec3 rd = this->len_radius * random_in_unit_disk();
    Vec3 offset = u * rd.get_x() + v * rd.get_y();
    Vec3 dir = this->lower_left_corner + s * this->horizontal + t * this->vertical - this->origin;
    return Ray(this->origin + offset, dir - offset);
}
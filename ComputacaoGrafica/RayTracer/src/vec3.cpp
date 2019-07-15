#include "vec3.h"

// Definindo o construtor da classe
Vec3:: Vec3() {}

Vec3::Vec3(float x, float y, float z)
: x(x), y(y), z(z) {}

// Definindo o destrutor da classe
Vec3::~Vec3() {}

// Métodos getter
float Vec3::get_x() const {
    return this->x;
}

float Vec3::get_y() const {
    return this->y;
}

float Vec3::get_z() const {
    return this->z;
}

// Definindo a norma do vetor
float Vec3::norm() const {
    float x2 = this->x * this->x;
    float y2 = this->y * this->y;
    float z2 = this->z * this->z;

    return sqrt(x2 + y2 + z2);
}

// Definindo método que retorna um vetor normalizado
Vec3 Vec3::normalize(const Vec3& v) {
    return v / v.norm();
}

// Definindo produto escalar entre dois vetores
float Vec3::dot(const Vec3& v, const Vec3& u) {
    return v.x * u.x + v.y * u.y + v.z * u.z;
}

// Definindo o produto vetorial entre dois vetores
Vec3 Vec3::cross(const Vec3& v, const Vec3& u) {
    float x = v.y * u.z - v.z * u.y;
    float y = v.x * u.z - v.z * u.x;
    float z = v.x * u.y - v.y * u.x;

    return Vec3(x, y, z);
}

// Definindo a raiz quadrada de um vetor
Vec3 sqrt(const Vec3& v) {
    return Vec3(sqrt(v.x), sqrt(v.y), sqrt(v.z));
}

// Definido a inversão do sentido de um vetor
Vec3 Vec3::operator-() const {
    return Vec3(-this->x, -this->y, -this->z);
}

// Definindo soma entre dois vetores
Vec3 operator+(const Vec3& v, const Vec3& u){
    return Vec3(v.x + u.x, v.y + u.y, v.z + u.z);
}

// Definindo a subtração entre dois vetores
Vec3 operator-(const Vec3& v, const Vec3& u) {
    return Vec3(v.x- u.x, v.y - u.y, v.z - u.z);
}

// Definindo a divisão de um vetor por escalar
Vec3 operator/(const Vec3& v, const float val) {
    return v * (float) (1 / val);
}

// Definindo o produto de um vetor por outro (multiplicar o "xyz" de um pelo do outro)
Vec3 operator*(const Vec3& v, const Vec3& u) {
    return Vec3(v.x * u.x, v.y * u.y, v.z * u.z);
}

// Definindo produto de um vetor por escalar
Vec3 operator*(const float val, const Vec3& v) {
    return Vec3(val * v.x, val * v.y, val * v.z);
}

Vec3 operator*(const Vec3& v, const float val) {
    return val * v;
}

// Definindo o stream de saída para nossa classe
std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << v.x << " " << v.y << " " << v.z;
    return os;
}
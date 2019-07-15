#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class Vec3 {
    // Definindo os atributos da classe
    private:
        float x, y, z;

    // Definindo os métodos da classe
    public:
        // Construtor e destrutor
        Vec3();
        Vec3(float x, float y, float z);
        ~Vec3();

        // Métodos getter
        float get_x() const;
        float get_y() const;
        float get_z() const;
        
        // Métodos da classe
        float norm() const;

        static Vec3 normalize(const Vec3& v);
        static float dot(const Vec3& v, const Vec3& u);
        static Vec3 cross(const Vec3& v, const Vec3& u);

        friend Vec3 sqrt(const Vec3& v);

        // Overload de operadores
        Vec3 operator-() const;
        friend Vec3 operator+(const Vec3& v, const Vec3& u);
        friend Vec3 operator-(const Vec3& v, const Vec3& u);
        friend Vec3 operator/(const Vec3& v, const float val);
        friend Vec3 operator*(const Vec3& v, const Vec3& u);
        friend Vec3 operator*(const Vec3& v, const float val);
        friend Vec3 operator*(const float val, const Vec3& v);
        friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
};

#endif
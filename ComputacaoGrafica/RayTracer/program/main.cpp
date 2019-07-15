#include <iostream>
#include <fstream>
#include <cfloat>
#include <cmath>
#include <vector>

#include "hitable_list.h"
#include "camera.h"
#include "hitable.h"
#include "sphere.h"
#include "vec3.h"
#include "ray.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

// Definindo a altura e largura da imagem de saída
#define SCREEN_WIDTH  200
#define SCREEN_HEIGHT 100
#define ANTI_ALIASING 100

// Definindo função que retorna a cor do pixel
Vec3 raytrace(const Ray& ray, const HitableList& world, int depth) {
    struct HitRecord rec;

    if (world.hit(ray, 0.001, FLT_MAX, rec)) {
        Ray scattered;
        Vec3 attenuation;

        if (depth < 50 && rec.mat->scatter(ray, rec, attenuation, scattered))
            return attenuation * raytrace(scattered, world, depth + 1);
        else
            return Vec3(0, 0, 0);
    }

    Vec3 dir = Vec3::normalize(ray.get_dir());
    float t = 0.5 * (dir.get_y() + 1);
    return (1 - t) * Vec3(1, 1, 1) + t * Vec3(0.5, 0.7, 1.0);
}

// Definindo a função principal
int main(int argc, const char **argv) {
    // Abrindo o arquivo de saída
    std::ofstream f("output.ppm");

    // Imprimindo o "cabeçalho" de um arquivo .ppm
    f << "P3\n";
    f << SCREEN_WIDTH << " " << SCREEN_HEIGHT << "\n";
    f << 255 << "\n";

    // Definindo nossa camera
    Camera cam;

    // Definindo os objetos
    std::vector<Hitable*> objects;
    objects.push_back(new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.1, 0.2, 0.5))));
    objects.push_back(new Sphere(Vec3(0, -100.5, -1), 100, new Lambertian(Vec3(0.8, 0.8, 0.0))));
    objects.push_back(new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.2)));
    objects.push_back(new Sphere(Vec3(-1, 0, -1), 0.5, new Dielectric(1.5)));
    objects.push_back(new Sphere(Vec3(-1, 0, -1), -0.45, new Dielectric(1.5)));

    // Criando nossa lista de objetos hitable
    HitableList world(objects);

    // Inserindo a cor de cada pixel no arquivo de saída
    for (int j = SCREEN_HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            Vec3 outColor(0, 0, 0);
            for (int k = 0; k < ANTI_ALIASING; k++) {
                float u = (float) (i + drand48()) / SCREEN_WIDTH;
                float v = (float) (j + drand48()) / SCREEN_HEIGHT;

                Ray ray = cam.shoot_ray(u, v);
                outColor = outColor + raytrace(ray, world, 0);
            }

            outColor = outColor / ANTI_ALIASING;
            f << 255.99 * sqrt(outColor) << "\n";
        }
    }

    f.close();
}
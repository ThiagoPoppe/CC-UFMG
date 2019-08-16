#include <iostream>
#include <fstream>
#include <cfloat>

#include "hitable_list.h"
#include "camera.h"
#include "hitable.h"
#include "vec3.h"
#include "ray.h"

// Definindo a altura e largura da imagem de saída
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080
#define ANTI_ALIASING 100

// Definindo função que retorna a cor do pixel
Vec3 raytrace(const Ray& ray, const Hitable* world, int depth) {
    struct HitRecord rec;
    
    // Detectou algum objeto
    if (world->hit(ray, 0.001, FLT_MAX, rec)) {
        Ray scattered;
        Vec3 attenuation;

        if (depth < 50 && rec.mat->scatter(ray, rec, attenuation, scattered))
            return attenuation * raytrace(scattered, world, depth + 1);
        else
            return Vec3(0, 0, 0);
    }

    // Colorindo o background
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
    Vec3 cam_origin(13, 2, 3);
    Vec3 look_at(0, 0, 0);
    Vec3 vup(0, 1, 0);
    float focus_dist = 10.0;
    float aperture = 0.0;

    Camera cam(cam_origin, look_at, vup, 20, (float) SCREEN_WIDTH / SCREEN_HEIGHT, aperture, focus_dist);

    // Criando nossa cena
    Hitable* world = HitableList::random_scene();

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
    delete world;
}
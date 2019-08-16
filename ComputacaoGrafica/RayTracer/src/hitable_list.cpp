#include "hitable_list.h"

#include "sphere.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

// Definindo o construtor da classe
HitableList::HitableList(std::vector<Hitable*> l)
: objs(l) {}

// Definindo o destrutor da classe
HitableList::~HitableList() {
    objs.clear();
}

// Definindo método que cria uma cena aleatória
Hitable* HitableList::random_scene() {
    // Criando um vector de objetos
    std::vector<Hitable*> objects;

    // Inserindo o chão da cena
    objects.push_back(new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(0.5, 0.5, 0.5))));

    for (int i = -11; i < 11; i++) {
        for (int j = -11; j < 11; j++) {
            // Escolhendo aleatóriamente o material do objeto a ser inserido
            float material = drand48();
            
            // Definindo o centro da esfera a ser inserida
            Vec3 center(i + 0.9 * drand48(), 0.2, j + 0.9 * drand48());

            // Verificando se a esfera atravessa o chão
            if ((center - Vec3(4, 0.2, 0)).norm() > 0.9) {
                // Material será difuso
                if (material < 0.8) {
                    float r = drand48() * drand48();
                    float g = drand48() * drand48();
                    float b = drand48() * drand48();
                    objects.push_back(new Sphere(center, 0.2, new Lambertian(Vec3(r, g, b))));
                }

                // Material será metálico
                else if (material < 0.95) {
                    float x = 0.5 * (1 + drand48());
                    float y = 0.5 * (1 + drand48());
                    float z = 0.5 * (1 + drand48());
                    objects.push_back(new Sphere(center, 0.2, new Metal(Vec3(x, y, z), 0.5 * drand48())));
                }

                // Material será dieléctrico
                else {
                    objects.push_back(new Sphere(center, 0.2, new Dielectric(1.5)));
                }
            }
        }
    }

    // Inserindo 3 esferas maiores de cada material
    objects.push_back(new Sphere(Vec3(-4, 1, 0), 1, new Lambertian(Vec3(0.4, 0.2, 0.1))));
    objects.push_back(new Sphere(Vec3(4, 1, 0), 1, new Metal(Vec3(0.7, 0.6, 0.5), 0)));
    objects.push_back(new Sphere(Vec3(0, 1, 0), 1, new Dielectric(1.5)));
    
    return new HitableList(objects);
}

// Definindo métodos da herança
bool HitableList::hit(const Ray& ray, float t_min, float t_max, struct HitRecord& rec) const {
    bool hasHit = false;
    float closest = t_max;
    HitRecord aux;

    for (auto obj : this->objs) {
        if (obj->hit(ray, t_min, closest, aux)) {
            hasHit = true;
            closest = aux.t;
            rec = aux;
        }
    }

    return hasHit;
}
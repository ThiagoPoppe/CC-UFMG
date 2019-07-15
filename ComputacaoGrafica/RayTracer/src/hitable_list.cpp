#include "hitable_list.h"

// Definindo o construtor da classe
HitableList::HitableList(std::vector<Hitable*> l)
: objs(l) {}

// Definindo o destrutor da classe
HitableList::~HitableList() {
    objs.clear();
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
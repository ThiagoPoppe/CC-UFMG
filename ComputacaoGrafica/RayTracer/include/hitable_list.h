#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include <vector>
#include "hitable.h"

class HitableList : public Hitable {
    // Definindo os atributos da classe
    private:
        std::vector<Hitable*> objs;
    
    public:
        // Construtor e destrutor
        HitableList(std::vector<Hitable*> l);
        ~HitableList();

        // Definindo métodos da herança
        virtual bool hit(const Ray& ray, float t_min, float t_max, struct HitRecord& rec) const;
};

#endif 
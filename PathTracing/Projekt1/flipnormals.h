#ifndef FLIPNORMALS_H
#define FLIPNORMALS_H

#include "hitable.h"

class FlipNormals: public Hitable {
public:
    FlipNormals(Hitable *p);
    virtual bool hit(const Ray& ray, float t_min, float t_max, hitRecord& rec) const;
    Hitable *ptr;
};

#endif // FLIPNORMALS_H

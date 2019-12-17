#ifndef YZRECT_H
#define YZRECT_H

#include "hitable.h"

class yzRect: public Hitable {
public:
    yzRect(float y0, float y1, float z0, float z1, float k, Material *mat);
    virtual bool hit(const Ray& ray, float t_min, float t_max, hitRecord& rec) const;
    float y0, y1, z0, z1, k;
    Material *mat;
};

#endif // YZRECT_H

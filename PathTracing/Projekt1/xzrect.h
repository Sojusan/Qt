#ifndef XZRECT_H
#define XZRECT_H

#include "hitable.h"

class xzRect: public Hitable {
public:
    xzRect(float x0, float x1, float z0, float z1, float k, Material *mat);
    virtual bool hit(const Ray& ray, float t_min, float t_max, hitRecord& rec) const;
    float x0, x1, z0, z1, k;
    Material *mat;
};

#endif // XZRECT_H

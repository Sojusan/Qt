#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"
#include "material.h"

struct hitRecord {
    float t;
    float u;
    float v;
    QVector3D p;
    QVector3D normal;
    Material *matPtr;
};

class Hitable
{
public:
    virtual bool hit(const Ray& ray, float t_min, float t_max, hitRecord& rec) const = 0;
};

#endif // HITABLE_H

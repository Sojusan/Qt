#ifndef XYRECT_H
#define XYRECT_H

#include "hitable.h"

class xyRect : public Hitable{
public:
    xyRect(float x0, float x1, float y0, float y1, float k, Material *mat);
    virtual bool hit(const Ray& ray, float t_min, float t_max, hitRecord& rec) const;
    float x0, x1, y0, y1, k;
    Material *mat;
};

#endif // XYRECT_H

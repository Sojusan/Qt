#include "flipnormals.h"

FlipNormals::FlipNormals(Hitable *p)
{
    ptr = p;
}

bool FlipNormals::hit(const Ray &ray, float t_min, float t_max, hitRecord &rec) const
{
    if (ptr->hit(ray, t_min, t_max, rec)) {
        rec.normal = -rec.normal;
        return true;
    }
    else {
        return false;
    }
}

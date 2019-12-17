#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"

class HitableList: public Hitable {
public:
    HitableList();
    HitableList(Hitable **l, int n);
    virtual bool hit(const Ray& ray, float tmin, float tmax, hitRecord& rec) const;
    Hitable **list;
    int listSize;
};

#endif // HITABLELIST_H

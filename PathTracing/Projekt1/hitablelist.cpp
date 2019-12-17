#include "hitablelist.h"

HitableList::HitableList()
{

}

HitableList::HitableList(Hitable **l, int n)
{
    list = l;
    listSize = n;
}

bool HitableList::hit(const Ray &ray, float tmin, float tmax, hitRecord &rec) const
{
    hitRecord tempRec;
    bool hitAnything = false;
    float closestSoFar = tmax;
    for (int i = 0; i < listSize; i++) {
        if (list[i]->hit(ray, tmin, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}

#include "xzrect.h"

xzRect::xzRect(float x0, float x1, float z0, float z1, float k, Material *mat)
{
    this->x0 = x0;
    this->x1 = x1;
    this->z0 = z0;
    this->z1 = z1;
    this->k = k;
    this->mat = mat;
}

bool xzRect::hit(const Ray &ray, float t_min, float t_max, hitRecord &rec) const
{
    float t = (k - ray.origin().y()) / ray.direction().y();
    if (t < t_min || t > t_max) {
        return false;
    }
    float x = ray.origin().x() + t * ray.direction().x();
    float z = ray.origin().z() + t * ray.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1) {
        return false;
    }
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.matPtr = mat;
    rec.p = ray.getPointAtRay(t);
    rec.normal = QVector3D(0, 1, 0);
    return true;
}

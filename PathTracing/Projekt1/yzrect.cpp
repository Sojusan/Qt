#include "yzrect.h"

yzRect::yzRect(float y0, float y1, float z0, float z1, float k, Material *mat)
{
    this->y0 = y0;
    this->y1 = y1;
    this->z0 = z0;
    this->z1 = z1;
    this->k = k;
    this->mat = mat;
}

bool yzRect::hit(const Ray &ray, float t_min, float t_max, hitRecord &rec) const
{
    float t = (k - ray.origin().x()) / ray.direction().x();
    if (t < t_min || t > t_max) {
        return false;
    }
    float y = ray.origin().y() + t * ray.direction().y();
    float z = ray.origin().z() + t * ray.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1) {
        return false;
    }
    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.matPtr = mat;
    rec.p = ray.getPointAtRay(t);
    rec.normal = QVector3D(1, 0, 0);
    return true;
}

#include "xyrect.h"

xyRect::xyRect(float x0, float x1, float y0, float y1, float k, Material *mat)
{
    this->x0 = x0;
    this->x1 = x1;
    this->y0 = y0;
    this->y1 = y1;
    this->k = k;
    this->mat = mat;
}

bool xyRect::hit(const Ray &ray, float t_min, float t_max, hitRecord &rec) const
{
    float t = (k - ray.origin().z()) / ray.direction().z();
    if (t < t_min || t > t_max) {
        return false;
    }
    float x = ray.origin().x() + t * ray.direction().x();
    float y = ray.origin().y() + t * ray.direction().y();
    if (x < x0 || x > x1 ||  y < y0 || y > y1) {
        return false;
    }
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    rec.matPtr = mat;
    rec.p = ray.getPointAtRay(t);
    rec.normal = QVector3D(0, 0, 1);
    return true;
}

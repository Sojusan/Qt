#include "sphere.h"

Sphere::Sphere()
{

}

Sphere::Sphere(QVector3D center, float radius)
{
    this->center = center;
    this->radius = radius;
}

Sphere::Sphere(QVector3D center, float r, Material *material)
{
    this->center = center;
    this->radius = r;
    this->material = material;
}

bool Sphere::hit(const Ray &ray, float tmin, float tmax, hitRecord &rec) const
{
    rec.matPtr = material;
    QVector3D oc = ray.origin() - center;
    float a = QVector3D::dotProduct(ray.direction(), ray.direction());
    float b = QVector3D::dotProduct(oc, ray.direction());
    float c = QVector3D::dotProduct(oc, oc) - radius * radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - std::sqrt(b*b - a*c)) / a;
        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = ray.getPointAtRay(rec.t);
            rec.normal = (rec.p - center) / radius;
            getSphereUV((rec.p - center) / radius, rec.u, rec.v);
            return true;
        }
        temp = (-b + std::sqrt(b*b - a*c)) / a;
        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = ray.getPointAtRay(rec.t);
            rec.normal = (rec.p - center) / radius;
            getSphereUV((rec.p - center) / radius, rec.u, rec.v);
            return true;
        }
    }
    return false;
}

void Sphere::getSphereUV(const QVector3D &p, float &u, float &v) const
{
    float phi = atan2f(p.z(), p.x());
    float theta = asinf(p.y());
    u = 1 - (phi + float(M_PI)) / (2 * float(M_PI));
    v = (theta + float(M_PI) / 2) / float(M_PI);
}

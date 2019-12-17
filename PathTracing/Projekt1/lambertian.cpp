#include "lambertian.h"

Lambertian::Lambertian(const QVector3D &a)
{
    albedo = a;
}

bool Lambertian::scatter(const Ray &rayIn, QVector3D &p, QVector3D &normal, QVector3D &attenuation, Ray &scattered) const
{
    QVector3D target = p + normal + randomInUnitSphere();
    scattered = Ray(p, target - p);
    attenuation = albedo;
    return true;
}

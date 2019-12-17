#include "metal.h"

Metal::Metal(const QVector3D &a, float f)
{
    albedo = a;
    if (f < 1) {
        fuzz = f;
    }
    else {
        fuzz = 1;
    }
}

bool Metal::scatter(const Ray &rayIn, QVector3D &p, QVector3D &normal, QVector3D &attenuation, Ray &scattered) const
{
    rayIn.direction().normalize();
    QVector3D reflected = reflect(rayIn.direction(), normal);
    scattered = Ray(p, reflected + fuzz * randomInUnitSphere());
    attenuation = albedo;
    return (QVector3D::dotProduct(scattered.direction(), normal) > 0);
}

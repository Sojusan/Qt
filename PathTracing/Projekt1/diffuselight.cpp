#include "diffuselight.h"

DiffuseLight::DiffuseLight(Texture *a)
{
    lightEmit = a;
}

bool DiffuseLight::scatter(const Ray &rayIn, QVector3D &p, QVector3D &normal, QVector3D &attenuation, Ray &scattered) const
{
    return false;
}

QVector3D DiffuseLight::emitted(float u, float v, const QVector3D &p) const
{
    return lightEmit->value(u, v, p);
}

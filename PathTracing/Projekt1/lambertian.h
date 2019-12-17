#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian: public Material {
public:
    Lambertian(const QVector3D &a);
    virtual bool scatter(const Ray &rayIn, QVector3D& p, QVector3D& normal, QVector3D& attenuation, Ray& scattered) const;
    QVector3D albedo;
};

#endif // LAMBERTIAN_H

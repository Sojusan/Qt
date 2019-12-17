#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include <qmath.h>

class Material{
public:
    QVector3D reflect(const QVector3D& v, const QVector3D& n) const;
    QVector3D randomInUnitSphere() const;
    float schlick(float cosine, float ref_idx) const;
    bool refract(const QVector3D& v, const QVector3D& n, float niOverNt, QVector3D& refracted) const;
    virtual bool scatter(const Ray& rayIn, QVector3D& p, QVector3D& normal, QVector3D& attenuation, Ray& scattered) const = 0;
    virtual QVector3D emitted(float u, float v, const QVector3D& p) const;
};

#endif // MATERIAL_H

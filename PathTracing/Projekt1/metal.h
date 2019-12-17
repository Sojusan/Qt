#ifndef METAL_H
#define METAL_H

#include "material.h"

class Metal: public Material {
public:
    Metal(const QVector3D& a, float f);
    virtual bool scatter(const Ray &rayIn, QVector3D& p, QVector3D& normal, QVector3D& attenuation, Ray& scattered) const;
    QVector3D albedo;
    float fuzz;
};

#endif // METAL_H

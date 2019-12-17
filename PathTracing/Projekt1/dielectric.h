#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

class Dielectric: public Material {
public:
    Dielectric(float ri);
    virtual bool scatter(const Ray& rayIn, QVector3D& p, QVector3D& normal, QVector3D& attenuation, Ray& scattered) const;
    float ref_idx;
};

#endif // DIELECTRIC_H

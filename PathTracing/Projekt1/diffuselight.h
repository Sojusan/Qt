#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H

#include "material.h"
#include "texture.h"

class DiffuseLight: public Material{
public:
    DiffuseLight(Texture *a);
    virtual bool scatter(const Ray& rayIn, QVector3D& p, QVector3D& normal, QVector3D& attenuation, Ray& scattered) const;
    virtual QVector3D emitted(float u, float v, const QVector3D& p) const;
    Texture *lightEmit;
};

#endif // DIFFUSELIGHT_H

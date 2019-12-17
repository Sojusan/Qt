#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"
#include <qmath.h>

class Sphere: public Hitable {
public:
    Sphere();
    Sphere(QVector3D center, float r);
    Sphere(QVector3D center, float r, Material* material);
    virtual bool hit(const Ray& ray, float tmin, float tmax, hitRecord& rec) const;
    void getSphereUV(const QVector3D& p, float& u, float& v) const;
    QVector3D center;
    float radius;
    Material* material;
};

#endif // SPHERE_H

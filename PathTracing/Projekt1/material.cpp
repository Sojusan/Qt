#include "material.h"

QVector3D Material::reflect(const QVector3D &v, const QVector3D &n) const
{
    return v - 2*QVector3D::dotProduct(v, n) * n;
}

QVector3D Material::randomInUnitSphere() const
{
    QVector3D p;
    do {
        p = 2.0 * QVector3D(float(drand48()), float(drand48()), float(drand48())) - QVector3D(1, 1, 1);
    } while (p.lengthSquared() >= 1.0f);
    return p;
}

float Material::schlick(float cosine, float ref_idx) const
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * powf((1 - cosine), 5);
}

bool Material::refract(const QVector3D &v, const QVector3D &n, float niOverNt, QVector3D &refracted) const
{
    v.normalized();
    float dt = QVector3D::dotProduct(v, n);
    float discriminant = 1.0f - niOverNt * niOverNt *  (1 - dt * dt);
    if (discriminant > 0) {
        refracted = niOverNt * (v - n * dt) - n * sqrtf(discriminant);
        return true;
    }
    else {
        return false;
    }
}

QVector3D Material::emitted(float u, float v, const QVector3D &p) const
{
    return QVector3D(0, 0, 0);
}

#include "dielectric.h"

Dielectric::Dielectric(float ri)
{
    ref_idx = ri;
}

bool Dielectric::scatter(const Ray &rayIn, QVector3D &p, QVector3D& normal, QVector3D &attenuation, Ray &scattered) const
{
    QVector3D outwardNormal;
    QVector3D reflected = reflect(rayIn.direction(), normal);
    float niOverNt;
    attenuation = QVector3D(1.0, 1.0, 1.0);
    QVector3D refracted;
    float reflect_prob;
    float cosine;
    if (QVector3D::dotProduct(rayIn.direction(), normal) > 0) {
        outwardNormal = -normal;
        niOverNt = ref_idx;
        cosine = ref_idx * QVector3D::dotProduct(rayIn.direction(), normal) / rayIn.direction().length();
    }
    else {
        outwardNormal = normal;
        niOverNt = 1.0f / ref_idx;
        cosine = -QVector3D::dotProduct(rayIn.direction(), normal) / rayIn.direction().length();
    }
    if (refract(rayIn.direction(), outwardNormal, niOverNt, refracted)) {
        reflect_prob = schlick(cosine, ref_idx);
    }
    else {
        //scattered = Ray(p, reflected);
        reflect_prob = 1.0;
    }
    if (float(drand48()) < reflect_prob) {
        scattered = Ray(p, reflected);
    }
    else {
        scattered = Ray(p, refracted);
    }
    return true;
}


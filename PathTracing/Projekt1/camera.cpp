#include "camera.h"

Camera::Camera(QVector3D lookFrom, QVector3D lookAt, QVector3D vup, float vfov, float aspect){
    QVector3D u, v, w;
    float theta = vfov * float(M_PI) / 180;
    float halfHeight = tanf(theta / 2);
    float halfWidth = aspect * halfHeight;
    origin = lookFrom;
    w = lookFrom - lookAt;
    w.normalize();
    u = QVector3D::crossProduct(vup, w);
    u.normalize();
    v = QVector3D::crossProduct(w, u);
    lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
    horizontal = 2 * halfWidth * u;
    vertical = 2 * halfHeight * v;
}

Ray Camera::getRay(float u, float v)
{
    return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}

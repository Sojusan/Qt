#include "ray.h"

Ray::Ray()
{

}

Ray::Ray(const QVector3D &origin, const QVector3D &direction)
{
    A = origin;
    B = direction;
}

QVector3D Ray::origin() const
{
    return A;
}

QVector3D Ray::direction() const
{
    return B;
}

QVector3D Ray::getPointAtRay(float t) const
{
    return A + t * B;
}



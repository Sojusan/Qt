#ifndef RAY_H
#define RAY_H

#include <QVector3D>

class Ray
{
public:
    Ray();
    Ray(const QVector3D& origin,const QVector3D& direction);
    QVector3D origin() const;
    QVector3D direction() const;
    QVector3D getPointAtRay(float t) const;

private:
    QVector3D A;
    QVector3D B;
};

#endif // RAY_H

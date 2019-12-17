#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include <qmath.h>

class Camera {
public:
    Camera(QVector3D lookFrom, QVector3D lookAt, QVector3D vup ,float vfov, float aspect);
    Ray getRay(float u, float v);
private:
    QVector3D lowerLeftCorner;
    QVector3D horizontal;
    QVector3D vertical;
    QVector3D origin;
};

#endif // CAMERA_H

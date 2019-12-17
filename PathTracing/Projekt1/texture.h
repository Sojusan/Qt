#ifndef TEXTURE_H
#define TEXTURE_H

#include <QVector3D>

class Texture{
public:
    virtual QVector3D value(float u, float v, const QVector3D& p) const = 0;
};

#endif // TEXTURE_H

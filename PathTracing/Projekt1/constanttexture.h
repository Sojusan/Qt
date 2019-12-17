#ifndef CONSTANTTEXTURE_H
#define CONSTANTTEXTURE_H

#include "texture.h"

class ConstantTexture: public Texture{
public:
    ConstantTexture();
    ConstantTexture(QVector3D color);
    virtual QVector3D value(float u, float v, const QVector3D& p) const;
    QVector3D color;
};

#endif // CONSTANTTEXTURE_H

#include "constanttexture.h"

ConstantTexture::ConstantTexture()
{

}

ConstantTexture::ConstantTexture(QVector3D color)
{
    this->color = color;
}

QVector3D ConstantTexture::value(float u, float v, const QVector3D &p) const
{
    return color;
}

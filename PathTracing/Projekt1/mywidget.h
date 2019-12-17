#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QStack>
#include <QWidget>
#include <armadillo>
#include <QVector3D>
#include <Qt3DRender/QRayCaster>
#include "ray.h"
#include "camera.h"
#include "hitablelist.h"
#include "sphere.h"
#include "lambertian.h"
#include "constanttexture.h"
#include "xyrect.h"
#include "xzrect.h"
#include "yzrect.h"
#include "flipnormals.h"
#include "diffuselight.h"
#include "dielectric.h"
#include "metal.h"

using namespace arma;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    QImage im;


    void paintEvent(QPaintEvent *);
    void putPixel(int, int, int, int, int);

    void test();
    void betterTest();
    void anotherTest();
    void generate(int x, int y, int z, int x2, int y2, int z2, int x3, int y3, int z3);
    QVector3D color(const Ray& ray, Hitable *world, int depth);
    QVector3D randomInUnitSphere();

    Hitable *randomScene();
    Hitable *simpleLight();
    Hitable *cornellBox();

    void cameraTest();
    void cameraTest(int x, int x2, int x3, int y, int y2, int y3, int z, int z2, int z3);
protected:

private:


signals:

public slots:


};

#endif // MYWIDGET_H

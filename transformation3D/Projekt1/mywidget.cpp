#include "mywidget.h"

#include <QColorDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <qmath.h>
#include <QtMath>
#include <algorithm>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent), im(900, 900, QImage::Format_RGB888)
{
    fillCubeVector();
    fillToDrawVector(focal);
    pointsToDraw = transformedPoints3D;
}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
    im.fill(Qt::black);
    drawCube();
}

void MyWidget::putPixel(int x, int y, int r, int g, int b)
{
    if (x < 0 || x >= im.width() || y < 0 || y >= im.height())
    {
        return;
    }
    else
    {
        uchar *p = im.scanLine(y);
        p[x * 3 + 0] = uchar(r);
        p[x * 3 + 1] = uchar(g);
        p[x * 3 + 2] = uchar(b);
        update();
    }
}

void MyWidget::putPixelAtImage(QImage *im, int x, int y, int r, int g, int b)
{
    if (x < 0 || x >= im->width() || y < 0 || y >= im->height())
    {
        return;
    }
    else
    {
        uchar *p = im->scanLine(y);
        p[x * 4 + 0] = uchar(r);
        p[x * 4 + 1] = uchar(g);
        p[x * 4 + 2] = uchar(b);
        update();
    }
}

void MyWidget::putRect(int x, int y, int w, int h, int r, int g, int b)
{
    for(int i = x; i < x + w; i++)
    {
        for (int j = y; j < y + h; j++)
        {
            putPixel(i, j, r, g, b);
        }
    }
}

void MyWidget::putRectAtImage(QImage *image, int x, int y, int w, int h, int r, int g, int b)
{
    for(int i = x; i < x + w; i++)
    {
        for (int j = y; j < y + h; j++)
        {
            putPixelAtImage(image, i, j, r, g, b);
        }
    }
}

void MyWidget::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b)
{
    float t;
    int x, y;

    if (abs(x2 - x1) >= abs(y2 - y1) && x1 <= x2) // [-45, 45]
    {
        for (x = x1; x <= x2; x++)
        {
            t = float((x - x1)) / float((x2 - x1));
            y = int(round(y1 + double(t) * (y2 - y1)));
            putPixel(x, y, r, g, b);
        }
    }
    if (abs(x2 - x1) >= abs(y2 - y1) && x1 > x2) // [135, 225]
    {
        for (x = x2; x <= x1; x++)
        {
            t = float((x - x1)) / float((x2 - x1));
            y = int(round(y1 + double(t) * (y2 - y1)));
            putPixel(x, y, r, g, b);
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 > y2) // [45, 135]
    {
        for (y = y2; y <= y1; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(round(x1 + double(t) * (x2 - x1)));
            putPixel(x, y, r, g, b);
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 <= y2) // [225, 315]
    {
        for (y = y1; y <= y2; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(round(x1 + double(t) * (x2 - x1)));
            putPixel(x, y, r, g, b);
        }
    }
}

void MyWidget::fillCubeVector()
{
    points3D.push_back(QVector3D(-100, -100, -100));
    points3D.push_back(QVector3D(100, -100, -100));
    points3D.push_back(QVector3D(100, 100, -100));
    points3D.push_back(QVector3D(-100, 100, -100));
    points3D.push_back(QVector3D(-100, -100, 100));
    points3D.push_back(QVector3D(100, -100, 100));
    points3D.push_back(QVector3D(100, 100, 100));
    points3D.push_back(QVector3D(-100, 100, 100));
    transformedPoints3D = points3D;
}

QVector<QPointF> MyWidget::fillToDrawVector(int focal)
{
    QVector<QPointF> result;
    for (int i = 0; i < transformedPoints3D.size(); i++) {
        int x = transformedPoints3D[i].x() * focal / (transformedPoints3D[i].z() + focal) + 450;
        int y = transformedPoints3D[i].y() * focal / (transformedPoints3D[i].z() + focal) + 450;
        result.push_back(QPointF(x, y));
    }
    return result;
}

void MyWidget::drawCube()
{
    QVector<QPointF> points2D = fillToDrawVector(focal);
    for (int i = 0; i < 4; i++) {
        drawLine(points2D[i].x(), points2D[i].y(), points2D[(i+1)%4].x(), points2D[(i+1)%4].y(), 0, 0, 255);
        drawLine(points2D[i+4].x(), points2D[i+4].y(), points2D[(i+1)%4+4].x(),points2D[(i+1)%4+4].y(), 0, 255, 0);
        drawLine(points2D[i].x(), points2D[i].y(), points2D[i+4].x(), points2D[i+4].y(), 255, 0, 0);
    }
}

void MyWidget::transformation()
{
    mat T = translation();
    mat S = scalings();
    mat Rx = rotationsX();
    mat Ry = rotationsY();
    mat Rz = rotationsZ();
    mat Sh = shearing();
    mat M = T * Rz * Ry * Rx * Sh * S;
    for (int i = 0; i < points3D.length(); i++)
    {
        mat P (4, 1, fill::ones);
        P(0, 0) = pointsToDraw[i].x();
        P(1, 0) = pointsToDraw[i].y();
        P(2, 0) = pointsToDraw[i].z();
        mat result = M * P;
        transformedPoints3D[i].setX(result(0, 0));
        transformedPoints3D[i].setY(result(1, 0));
        transformedPoints3D[i].setZ(result(2, 0));
    }
    update();
}

mat MyWidget::translation()
{
    mat T(4, 4, fill::eye);
    T(0, 3) = translationX;
    T(1, 3) = translationY;
    T(2, 3) = translationZ;
    return T;
}

mat MyWidget::translation(int x, int y, int z)
{
    mat T(4, 4, fill::eye);
    T(0, 3) = x;
    T(1, 3) = y;
    T(2, 3) = z;
    return T;
}

mat MyWidget::scalings()
{
    mat S(4, 4, fill::eye);
    S(0, 0) = double(scalingX) / 100.0;
    S(1, 1) = double(scalingY) / 100.0;
    S(2, 2) = double(scalingZ) / 100.0;
    return S;
}

mat MyWidget::rotationsX()
{
    double radians = qDegreesToRadians(double(rotationX));
    mat R(4, 4, fill::eye);
    R(1, 1) = R(2, 2) = qCos(radians);
    R(2, 1) = qSin(radians);
    R(1, 2) = -qSin(radians);
    return R;
}

mat MyWidget::rotationsY()
{
    double radians = qDegreesToRadians(double(rotationY));
    mat R(4, 4, fill::eye);
    R(0, 0) = R(2, 2) = qCos(radians);
    R(0, 2) = qSin(radians);
    R(2, 0) = -qSin(radians);
    return R;
}

mat MyWidget::rotationsZ()
{
    double radians = qDegreesToRadians(double(rotationZ));
    mat R(4, 4, fill::eye);
    R(0, 0) = R(1, 1) = qCos(radians);
    R(1, 0) = qSin(radians);
    R(0, 1) = -qSin(radians);
    return R;
}

mat MyWidget::shearing()
{
    mat Shxy(4, 4, fill::eye);
    mat Shxz(4, 4, fill::eye);
    mat Shyz(4, 4, fill::eye);
    Shxy(2, 0) = Shxz(1, 0) = double(shearingX) / 100.0;
    Shxy(2, 1) = Shyz(0, 1) = double(shearingY) / 100.0;
    Shxz(1, 2) = Shyz(0, 2) = double(shearingZ) / 100.0;
    return Shxy*Shxz*Shyz;
}

void MyWidget::setXTranslation(int x)
{
    translationX = x;
    transformation();
}

void MyWidget::setYTranslation(int x)
{
    translationY = x;
    transformation();
}

void MyWidget::setZTranslation(int x)
{
    translationZ = x;
    transformation();
}

void MyWidget::setYScaling(int x)
{
    scalingY = x;
    transformation();
}

void MyWidget::setZScaling(int x)
{
    scalingZ = x;
    transformation();
}

void MyWidget::setXScaling(int x)
{
    scalingX = x;
    transformation();
}

void MyWidget::setXRotation(int x)
{
    rotationX = x;
    transformation();
}

void MyWidget::setYRotation(int x)
{
    rotationY = x;
    transformation();
}

void MyWidget::setZRotation(int x)
{
    rotationZ = x;
    transformation();
}

void MyWidget::setXShearing(int x)
{
    shearingX = x;
    transformation();
}

void MyWidget::setYShearing(int x)
{
    shearingY = x;
    transformation();
}

void MyWidget::setZShearing(int x)
{
    shearingZ = x;
    transformation();
}

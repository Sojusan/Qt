#include "mywidget.h"

#include <QColorDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <qmath.h>
#include <QtMath>
#include <algorithm>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent), im(1800, 600, QImage::Format_RGB888)
{
    drawVector.push_back(QPoint(1100, 200));
    drawVector.push_back(QPoint(1500, 200));
    drawVector.push_back(QPoint(1300, 500));

    imageVector.push_back(QPoint(390, 240));
    imageVector.push_back(QPoint(515, 240));
    imageVector.push_back(QPoint(450, 470));
    denominator = ((drawVector[1].x() - drawVector[0].x()) * (drawVector[2].y() - drawVector[0].y())) - ((drawVector[2].x() - drawVector[0].x()) * (drawVector[1].y() - drawVector[0].y()));
}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //p.drawImage(0, 0, im);
    p.drawImage(0, 0, *imageToWork);
    drawDrawTriangle();
    drawImageTriangle();
    scanLine();
   // imPrev = im;
   // update();
}

void MyWidget::mouseMoveEvent(QMouseEvent *e)
{
    int currentX = e->x();
    int currentY = e->y();
    *imageToWork = *image;
    QPoint movedPoint(currentX, currentY);
    if (currentX > 900) {
        for (int i = 0; i < drawVector.size(); i++)
        {
          if (drawVector[i] == foundPoint)
          {
            drawVector[i] = movedPoint;
            break;
          }
        }
    }
    else {
        for (int i = 0; i < imageVector.size(); i++)
        {
          if (imageVector[i] == foundPoint)
          {
            imageVector[i] = movedPoint;
            break;
          }
        }
    }
    foundPoint = movedPoint;
    drawDrawTriangle();
    drawImageTriangle();
    scanLine();
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    int startX = e->x();
    int startY = e->y();
    //imPrev = im;
    if (e->button() == Qt::LeftButton)
    {
        QPoint tmp(startX, startY);
        if (startX > 900) {
            foundPoint = findClosestPoint(tmp, drawVector);
        }
        else {
            foundPoint = findClosestPoint(tmp, imageVector);
        }
        update();
    }
    if (e->button() == Qt::MidButton)
    {

    }
    if (e->button() == Qt::RightButton)
    {

    }
}

QPoint MyWidget::findClosestPoint(QPoint p, QVector<QPoint> vector)
{
    int side = 10;
    QPoint tmp(-1, -1);
    for (int i = 0; i < vector.size(); i++)
    {
        if ((vector[i].x() - (side/2) <= p.x()) && (vector[i].x() + side >= p.x())
            && (vector[i].y() - (side/2) <= p.y()) && (vector[i].y() + side >= p.y()))
        {
            return vector[i];
        }
    }
    return tmp;
}

void MyWidget::scanLine()
{
    int yMin = drawVector[0].y();
    int yMax = drawVector[0].y();
    for (int i = 1; i < drawVector.size(); i++)
    {
        if (yMin > drawVector[i].y())
        {
            yMin = drawVector[i].y();
        }
        if (yMax < drawVector[i].y())
        {
            yMax = drawVector[i].y();
        }
    }
    for (int y = yMin; y <= yMax; y++)
    {
        QVector<int> xValues;
        for(int i = 0; i < drawVector.size(); i++)
        {
            int j = (i + 1) % drawVector.size();
            if (((y >= drawVector[i].y()) && (y < drawVector[j].y())) || ((y < drawVector[i].y()) && (y >= drawVector[j].y() )))
            {
                int x = int(drawVector[i].x() + (((float(drawVector[j].x() - drawVector[i].x())) / (drawVector[j].y() - drawVector[i].y())) * (y - drawVector[i].y())));
                xValues.push_back(x);
            }
        }
        std::sort(xValues.begin(), xValues.end());
        for (int j = 0; j < xValues.size()-1; j+=2)
        {
            int xT, yT;
            for (int i = xValues[j]; i < xValues[j + 1]; i++)
            {
                double v_counter = ((i - drawVector[0].x()) * (drawVector[2].y() - drawVector[0].y())) - ((drawVector[2].x() - drawVector[0].x()) * (y - drawVector[0].y()));
                double v = v_counter / denominator;
                double w_counter = ((drawVector[1].x() - drawVector[0].x()) * (y - drawVector[0].y())) - ((i - drawVector[0].x()) * (drawVector[1].y() - drawVector[0].y()));
                //double w_denominator = ((drawVector[1].x() - drawVector[0].x()) * (drawVector[2].y() - drawVector[0].y())) - ((drawVector[2].x() - drawVector[0].x()) * (drawVector[1].y() - drawVector[0].y()));
                double w = w_counter / denominator;
                double u = 1 - v - w;

                xT = u * imageVector[0].x() + v * imageVector[1].x() + w * imageVector[2].x();
                yT = u * imageVector[0].y() + v * imageVector[1].y() + w * imageVector[2].y();

                QColor color = image->pixelColor(xT,yT);
                imageToWork->setPixelColor(i, y, color);
            }
        }
    }
}

void MyWidget::mouseReleaseEvent(QMouseEvent * e)
{

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
        p[x * 4 + 0] = uchar(b);
        p[x * 4 + 1] = uchar(g);
        p[x * 4 + 2] = uchar(r);
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
            putPixelAtImage(imageToWork, x, y, r, g, b);
        }
    }
    if (abs(x2 - x1) >= abs(y2 - y1) && x1 > x2) // [135, 225]
    {
        for (x = x2; x <= x1; x++)
        {
            t = float((x - x1)) / float((x2 - x1));
            y = int(round(y1 + double(t) * (y2 - y1)));
            putPixelAtImage(imageToWork, x, y, r, g, b);
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 > y2) // [45, 135]
    {
        for (y = y2; y <= y1; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(round(x1 + double(t) * (x2 - x1)));
            putPixelAtImage(imageToWork, x, y, r, g, b);
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 <= y2) // [225, 315]
    {
        for (y = y1; y <= y2; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(round(x1 + double(t) * (x2 - x1)));
            putPixelAtImage(imageToWork, x, y, r, g, b);
        }
    }
}

void MyWidget::drawDrawTriangle()
{
    putRectAtImage(imageToWork, drawVector[0].x(), drawVector[0].y(), 10, 10, 255, 0, 0);
    putRectAtImage(imageToWork, drawVector[1].x(), drawVector[1].y(), 10, 10, 255, 0, 0);
    putRectAtImage(imageToWork, drawVector[2].x(), drawVector[2].y(), 10, 10, 255, 0, 0);
    drawLine(drawVector[0].x(), drawVector[0].y(), drawVector[1].x(), drawVector[1].y(), 255, 255, 255);
    drawLine(drawVector[1].x(), drawVector[1].y(), drawVector[2].x(), drawVector[2].y(), 255, 255, 255);
    drawLine(drawVector[2].x(), drawVector[2].y(), drawVector[0].x(), drawVector[0].y(), 255, 255, 255);
}

void MyWidget::drawImageTriangle()
{
    putRectAtImage(imageToWork, imageVector[0].x(), imageVector[0].y(), 10, 10, 255, 0, 0);
    putRectAtImage(imageToWork, imageVector[1].x(), imageVector[1].y(), 10, 10, 255, 0, 0);
    putRectAtImage(imageToWork, imageVector[2].x(), imageVector[2].y(), 10, 10, 255, 0, 0);
    drawLine(imageVector[0].x(), imageVector[0].y(), imageVector[1].x(), imageVector[1].y(), 255, 255, 255);
    drawLine(imageVector[1].x(), imageVector[1].y(), imageVector[2].x(), imageVector[2].y(), 255, 255, 255);
    drawLine(imageVector[2].x(), imageVector[2].y(), imageVector[0].x(), imageVector[0].y(), 255, 255, 255);
}

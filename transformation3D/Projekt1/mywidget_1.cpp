#include "mywidget.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <qmath.h>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent), im(1000, 600, QImage::Format_RGB888)
{

}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
}

void MyWidget::mouseMoveEvent(QMouseEvent *e)
{
    int currentX = e->x();
    int currentY = e->y();
    if (choice != "Krzywa" && choice != "B-Sklejane")
    {
        im.fill(Qt::black);
        if (choice == "Linia")
            drawLine(startX, startY, currentX, currentY, 255, 255, 255);
        if (choice == "Okrag")
        {
            R = sqrt((currentX-startX)*(currentX-startX) + (currentY-startY) * (currentY-startY));
            drawCircle(startX, startY, R, 255, 255, 255);
        }
        if (choice == "Elipsa")
        {
            x0 = (startX + currentX) / 2;
            y0 = (startY + currentY) / 2;
            R1 = abs(currentX - startX) / 2;
            R2 = abs(currentY - startY) / 2;
            drawEllipse(x0, y0, R1, R2, beta, 255, 255, 255);
        }
    }
    else
    {
        if (pointMovement == true)
        {
            im.fill(Qt::black);
            if ((choice == "Krzywa" || choice == "B-Sklejane") && !points.empty())
            {
                QPoint movedPoint(currentX, currentY);
                for (int i = 0; i < numberOfPoints; i++)
                {
                    if (points[i] == foundPoint)
                    {
                        points[i] = movedPoint;
                        break;
                    }
                }
                foundPoint = movedPoint;
                if (choice == "Krzywa")
                {
                    drawWholeBezierCurve(255,255,255);
                }
                else
                {
                    drawWholeSplineCurve(255,255,255);
                }
            }
        }
    }
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    startX = e->x();
    startY = e->y();
    if (e->button() == Qt::LeftButton) // dodawanie punktow
    {
        if (choice == "Krzywa")
        {
            QPoint point(startX, startY);
            putRect(startX, startY, 10, 10, 255, 0, 0);
            points.push_back(point);
            numberOfPoints++;

            if (numberOfPoints == 4 || ((numberOfPoints-4) % 3 == 0 && numberOfPoints > 4))
            {
                drawBezierCurve(points[numberOfPoints-4], points[numberOfPoints-3], points[numberOfPoints-2], points[numberOfPoints-1], 255, 255, 255);
            }
        }
        if (choice == "B-Sklejane")
        {
            QPoint point(startX, startY);
            putRect(startX, startY, 10, 10, 255, 0, 0);
            points.push_back(point);
            numberOfPoints++;

            if (numberOfPoints >= 4)
            {
                drawSplineCurve(points[numberOfPoints-4], points[numberOfPoints-3], points[numberOfPoints-2], points[numberOfPoints-1], 255, 255, 255);
            }
        }
    }
    if (e->button() == Qt::MidButton) // usuwanie punktow
    {
        im.fill(Qt::black);
        update();
        if ((choice == "Krzywa" || choice == "B-Sklejane") && !points.empty())
        {
            for (auto it = points.begin(); it != points.end(); it++)
            {
                if ((it->x() - startX < 10 && it->x() - startX > -10) && (it->y() - startY < 10 && it->y() - startY > -10))
                {
                    points.erase(it);
                    numberOfPoints--;
                    break;
                }
            }
            if (choice == "Krzywa")
            {
                drawWholeBezierCurve(255,255,255);
            }
            else
            {
                drawWholeSplineCurve(255,255,255);
            }
        }
    }
    if (e->button() == Qt::RightButton) // przesuwanie punktow
    {
        QPoint tmp(startX, startY);
        foundPoint = findClosestPoint(tmp);
        pointMovement = true;
        update();
    }
}

void MyWidget::mouseReleaseEvent(QMouseEvent * e)
{
    if (e->button() == Qt::RightButton)
    {
        if (pointMovement == true)
        {
            pointMovement = false;
        }
    }
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

void MyWidget::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b)
{
    float t;
    int x, y;

    if (abs(x2 - x1) >= abs(y2 - y1) && x1 <= x2) // [-45, 45]
    {
        for (x = x1; x <= x2; x++)
        {
            t = float((x - x1)) / float((x2 - x1));
            y = int(y1 + t * (y2 - y1));
            putPixel(x, y, r, g, b);
        }
    }
    if (abs(x2 - x1) >= abs(y2 - y1) && x1 > x2) // [135, 225]
    {
        for (x = x2; x <= x1; x++)
        {
            t = float((x - x1)) / float((x2 - x1));
            y = int(y1 + t * (y2 - y1));
            putPixel(x, y, r, g, b);
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 > y2) // [45, 135]
    {
        for (y = y2; y <= y1; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(x1 + t * (x2 - x1));
            putPixel(x, y, r, g, b);
        }
    }
    if (abs(x2 - x1) <= abs(y2 - y1) && y1 <= y2) // [225, 315]
    {
        for (y = y1; y <= y2; y++)
        {
            t = float((y - y1)) / float((y2 - y1));
            x = int(x1 + t * (x2 - x1));
            putPixel(x, y, r, g, b);
        }
    }
}

void MyWidget::drawCircle(int x0, int y0, int R, int r, int g, int b)
{
    float a = R / sqrt(2);
    for(int x = 0; x <= a; x++)
    {
        int y = sqrt(R*R - x*x);
        putPixel(x + x0, y + y0, r, g, b);
        putPixel(y + x0, x + y0, r, g, b);
        putPixel(-x + x0, y + y0, r, g, b);
        putPixel(-y + x0, x + y0, r, g, b);
        putPixel(-x + x0, -y + y0, r, g, b);
        putPixel(-y + x0, -x + y0, r, g, b);
        putPixel(x + x0, -y + y0, r, g, b);
        putPixel(y + x0, -x + y0, r, g, b);
    }
}

void MyWidget::drawEllipse(int x0, int y0, int R1, int R2, float Beta, int r, int g, int b)
{
    int N = 60;
    float prev_x, prev_y;
    Beta = Beta * M_PI / 180;
    for (int i = 0; i <= N; i++)
    {
        float Alpha = 2 * M_PI * i / N;
        float x = R1 * cos(Alpha);
        float y = R2 * sin(Alpha);
        float x_beta = cos(Beta) * x + (-sin(Beta)) * y;
        float y_beta = sin(Beta) * x + cos(Beta) * y;
        if (i > 0)
        {
            drawLine(prev_x + x0, prev_y + y0, x_beta + x0, y_beta + y0, r, g, b);
        }
        prev_x = x_beta;
        prev_y = y_beta;
    }
}

void MyWidget::drawBezierCurve(QPoint p0, QPoint p1, QPoint p2, QPoint p3, int r, int g, int b)
{
    int x, y;
    int prev_x, prev_y;
    int n = 20;
    for (int t = 0; t <= n; t++)
    {
        x = (1-(float)t/n)*(1-(float)t/n)*(1-(float)t/n)*p0.x() + 3*(1-(float)t/n)*(1-(float)t/n)*((float)t/n)*p1.x() + 3*(1-(float)t/n)*(float)((float)t/n)*((float)t/n)*p2.x() + ((float)t/n)*((float)t/n)*((float)t/n)*p3.x();
        y = (1-(float)t/n)*(1-(float)t/n)*(1-(float)t/n)*p0.y() + 3*(1-(float)t/n)*(1-(float)t/n)*((float)t/n)*p1.y() + 3*(1-(float)t/n)*(float)((float)t/n)*((float)t/n)*p2.y() + ((float)t/n)*((float)t/n)*((float)t/n)*p3.y();
        if (t > 0)
        {
            drawLine(prev_x, prev_y, x, y, r, g ,b);
        }
        prev_x = x;
        prev_y = y;
    }
}

void MyWidget::drawWholeBezierCurve(int r, int g, int b)
{
    int howMany;
    for (int i = 0; i < points.size(); i++)
    {
        putRect(points[i].x(), points[i].y(), 10, 10, 255, 0, 0);
    }
    if (numberOfPoints < 4)
    {
        howMany = 0;
        return;
    }
    else
    {
        howMany = 1 + (numberOfPoints - 4)/3;
    }
    for (int i = 0; i < howMany; i++)
    {
        drawBezierCurve(points[i*3], points[(i*3)+1], points[(i*3)+2], points[(i*3)+3], r, g, b);
    }
}

void MyWidget::drawSplineCurve(QPoint p0, QPoint p1, QPoint p2, QPoint p3, int r, int g, int b)
{
    int x, y;
    int prev_x, prev_y;
    int n = 20;
    for (int t = 0; t <= n; t++)
    {
        float T = (float)t/n;
        //x = (((-(T*T*T) + 3*T*T - 3*T + 1)/6) * p0.x()) + ((3*T*T*T - 6*T*T + 4)/6) * p1.x() + ((-3*T*T*T + 3*T*T + 3*T + 1)/6) * p2.x() + ((T*T*T)/6) * p3.x();
        x = (float)1/6 * (-(T*T*T) + 3*T*T - 3*T + 1) * p0.x()
                + (float)1/6 * (3*T*T*T - 6*T*T + 4) * p1.x()
                + (float)1/6 * (-3*T*T*T + 3*T*T + 3*T + 1) * p2.x()
                + (float)1/6 * T*T*T * p3.x();
        //y = (((-(T*T*T)+ 3*T*T - 3*T + 1)/6) * p0.y()) + ((3*T*T*T - 6*T*T + 4)/6) * p1.y() + ((-3*T*T*T + 3*T*T + 3*T + 1)/6) * p2.y() + ((T*T*T)/6) * p3.y();
        y = (float)1/6 * (-(T*T*T) + 3*T*T - 3*T + 1) * p0.y()
                + (float)1/6 * (3*T*T*T - 6*T*T + 4) * p1.y()
                + (float)1/6 * (-3*T*T*T + 3*T*T + 3*T + 1) * p2.y()
                + (float)1/6 * T*T*T * p3.y();
        if (t > 0)
        {
            drawLine(prev_x, prev_y, x, y, r, g ,b);
        }
        prev_x = x;
        prev_y = y;
    }
}

void MyWidget::drawWholeSplineCurve(int r, int g, int b)
{
    int howMany;
    if (numberOfPoints < 4)
    {
        howMany = 0;
        return;
    }
    else
    {
        howMany = 1 + (numberOfPoints - 4);
    }
    for (int i = 0; i < points.size(); i++)
    {
        putRect(points[i].x(), points[i].y(), 10, 10, 255, 0, 0);
    }
    for (int i = 0; i < howMany; i++)
    {
        drawSplineCurve(points[i], points[i+1], points[i+2], points[i+3], r, g, b);
    }
}

QPoint MyWidget::findClosestPoint(QPoint p)
{
    int side = 10;
    QPoint tmp(-1, -1);
    for (int i = 0; i < numberOfPoints; i++)
    {
        if ((points[i].x() - (side/2) <= p.x()) && (points[i].x() + side >= p.x())
            && (points[i].y() - (side/2) <= p.y()) && (points[i].y() + side >= p.y()))
        {
            return points[i];
        }
    }
    return tmp;
}

void MyWidget::setChoice(QString what)
{
    choice = what;
}

void MyWidget::setBeta(int x)
{
    beta = x;
    im.fill(Qt::black);
    drawEllipse(x0, y0, R1, R2, beta, 255, 255, 255);
}

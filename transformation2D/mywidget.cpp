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
    alphaImages[0].load("/home/rgrzegorczyk/Documents/Studia/Qt_creator/Alpha_Blending/black_screen.jpg");
    alphaImages[1].load("/home/rgrzegorczyk/Documents/Studia/Qt_creator/Alpha_Blending/krajobraz.jpg");
    alphaImages[2].load("/home/rgrzegorczyk/Documents/Studia/Qt_creator/Alpha_Blending/wilk.jpg");
    alphaImages[3].load("/home/rgrzegorczyk/Documents/Studia/Qt_creator/Alpha_Blending/kwiat.png");
    layoutValues[0] = 0;
    layoutValues[1] = 0;
    layoutValues[2] = 0;
    imageToWorkAlphaBlending = alphaImages[0];
    fillHouseVector();
}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //p.drawImage(0, 0, im);
    if (choice == "RGB/HSV")
    {
        p.drawImage(0, 0, imageToWork);
    }
    else if (choice == "Alpha Blending")
    {
        p.drawImage(0, 0, imageToWorkAlphaBlending);
    }
    else if (choice == "Translations2D")
    {
        p.drawImage(0, 0, im);
        im.fill(Qt::black);
        drawHouse();
    }
    else
    {
        p.drawImage(0, 0, im);
    }

   // imPrev = im;
   // update();
}

void MyWidget::mouseMoveEvent(QMouseEvent *e)
{
    int currentX = e->x();
    int currentY = e->y();
    if (choice != "Krzywa" && choice != "B-Sklejane" && choice != "ScanLine")
    {
        im.fill(Qt::black);
        //im = imPrev;
        if (choice == "Linia")
            drawLine(startX, startY, currentX, currentY, 255, 255, 255);
        if (choice == "Okrag")
        {
            R = float(sqrt((currentX-startX)*(currentX-startX) + (currentY-startY) * (currentY-startY)));
            drawCircle(startX, startY, int(R), 255, 255, 255);
        }
        if (choice == "Elipsa")
        {
            x0 = (startX + currentX) / 2;
            y0 = (startY + currentY) / 2;
            R1 = abs(currentX - startX) / 2;
            R2 = abs(currentY - startY) / 2;
            drawEllipse(x0, y0, int(R1), int(R2), beta, 255, 255, 255);
        }
    }
    else
    {
        if (pointMovement == true)
        {
            im.fill(Qt::black);
            //im = imPrev;
            if ((choice == "Krzywa" || choice == "B-Sklejane" || choice == "ScanLine") && !points.empty())
            {
                QPoint movedPoint(currentX, currentY);
                for (int i = 0; i < points.size(); i++)
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
                else if (choice == "B-Sklejane")
                {
                    drawWholeSplineCurve(255,255,255);
                }
                else if (choice == "ScanLine")
                {
                    drawScanLineFigure();
                }
            }
        }
    }
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    startX = e->x();
    startY = e->y();
    //imPrev = im;
    if (e->button() == Qt::LeftButton) // dodawanie punktow
    {
        if (checked == true)
        {
            QColor color = QColorDialog::getColor();
            floodFill(startX, startY, color);
        }
        else
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

void MyWidget::putPixelAtImage(QImage *im, int x, int y, int r, int g, int b)
{
    if (x < 0 || x >= im->width() || y < 0 || y >= im->height())
    {
        return;
    }
    else
    {
        uchar *p = im->scanLine(y);
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

void MyWidget::drawCircle(int x0, int y0, int R, int r, int g, int b)
{
    float a = float(R / sqrt(2));
    for(int x = 0; x <= a; x++)
    {
        int y = int(sqrt(R*R - x*x));
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
    float prev_x = 0, prev_y = 0;
    Beta = float(double(Beta) * M_PI / 180);
    for (int i = 0; i <= N; i++)
    {
        float Alpha = float(2 * M_PI * i / N);
        float x = float(R1 * cos(double(Alpha)));
        float y = float(R2 * sin(double(Alpha)));
        float x_beta = float(cos(double(Beta)) * double(x) + (-sin(double(Beta))) * double(y));
        float y_beta = float(sin(double(Beta)) * double(x) + cos(double(Beta)) * double(y));
        if (i > 0)
        {
            drawLine(int(prev_x) + x0, int(prev_y) + y0, int(x_beta) + x0, int(y_beta) + y0, r, g, b);
        }
        prev_x = x_beta;
        prev_y = y_beta;
    }
}

void MyWidget::drawBezierCurve(QPoint p0, QPoint p1, QPoint p2, QPoint p3, int r, int g, int b)
{
    int x, y;
    int prev_x = 0, prev_y = 0;
    int n = 20;
    for (int t = 0; t <= n; t++)
    {
        float T = float(t)/n;
        x = int((1-T)*(1-T)*(1-T)*p0.x() + 3*(1-T)*(1-T)*(T)*p1.x() + 3*(1-T)*float((T)*(T)*p2.x()) + (T)*(T)*(T)*p3.x());
        y = int((1-T)*(1-T)*(1-T)*p0.y() + 3*(1-T)*(1-T)*(T)*p1.y() + 3*(1-T)*float((T)*(T)*p2.y()) + (T)*(T)*(T)*p3.y());
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
        howMany = int(1 + (numberOfPoints - 4)/3);
    }
    for (int i = 0; i < howMany; i++)
    {
        drawBezierCurve(points[i*3], points[(i*3)+1], points[(i*3)+2], points[(i*3)+3], r, g, b);
    }
}

void MyWidget::drawSplineCurve(QPoint p0, QPoint p1, QPoint p2, QPoint p3, int r, int g, int b)
{
    int x, y;
    int prev_x = 0, prev_y = 0;
    int n = 20;
    for (int t = 0; t <= n; t++)
    {
        float T = float(t)/n;
        x = int(float(1)/6 * (-(T*T*T) + 3*T*T - 3*T + 1) * p0.x()
                + float(1)/6 * (3*T*T*T - 6*T*T + 4) * p1.x()
                + float(1)/6 * (-3*T*T*T + 3*T*T + 3*T + 1) * p2.x()
                + float(1)/6 * T*T*T * p3.x());
        y = int(float(1)/6 * (-(T*T*T) + 3*T*T - 3*T + 1) * p0.y()
                + float(1)/6 * (3*T*T*T - 6*T*T + 4) * p1.y()
                + float(1)/6 * (-3*T*T*T + 3*T*T + 3*T + 1) * p2.y()
                + float(1)/6 * T*T*T * p3.y());
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
    unsigned long howMany;
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

bool MyWidget::inBordersOfImage(int x, int y)
{
    if (x < 0 || x >= im.width() || y < 0 || y >= im.height())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool MyWidget::inBordersAtImage(QImage *im, int x, int y)
{
    if (x < 0 || x >= im->width() || y < 0 || y >= im->height())
    {
        return false;
    }
    else
    {
        return true;
    }
}

QColor MyWidget::getPixelColor(int x, int y)
{
    return im.pixelColor(x,y);
}

QColor MyWidget::getPixelColorAtImage(QImage *im, int x, int y)
{
    return im->pixelColor(x,y);
}

void MyWidget::floodFill(int x0, int y0, QColor color)
{
    int r,g,b,a;
    color.getRgb(&r,&g,&b,&a);
    if (!inBordersOfImage(x0, y0))
    {
        return;
    }
    QColor bg = getPixelColor(x0, y0);
    if (bg == color)
    {
        return;
    }
    stack.push(QPoint(x0,y0));
    while (!stack.empty())
    {
        QPoint tmp = stack.pop();
        if(!inBordersOfImage(tmp.x(),tmp.y()) || bg != getPixelColor(tmp.x(),tmp.y()))
        {
            continue;
        }
        putPixel(tmp.x(),tmp.y(),r,g,b);
        stack.push(QPoint(tmp.x() - 1, tmp.y()));
        stack.push(QPoint(tmp.x() + 1, tmp.y()));
        stack.push(QPoint(tmp.x(), tmp.y() - 1));
        stack.push(QPoint(tmp.x(), tmp.y() + 1));
    }
}

QPoint MyWidget::findClosestPoint(QPoint p)
{
    int side = 10;
    QPoint tmp(-1, -1);
    for (int i = 0; i < points.size(); i++)
    {
        if ((points[i].x() - (side/2) <= p.x()) && (points[i].x() + side >= p.x())
            && (points[i].y() - (side/2) <= p.y()) && (points[i].y() + side >= p.y()))
        {
            return points[i];
        }
    }
    return tmp;
}

void MyWidget::RGBtoHSV()
{
    double max, min;
    double delta;
    double r = red / 255.0;
    double g = green / 255.0;
    double b = blue / 255.0;
    max = qMax(qMax(r,g),b);
    min = qMin(qMin(r,g),b);
    valueV = max;
    delta = max - min;
    if (max != 0)
    {
        valueS = delta/max;
    }
    else
    {
        valueS = 0;
        valueH = -1;
        return;
    }

    if (max == r)
    {
        valueH = 60 * ((g - b) / delta);
    }
    else if (max == g)
    {
        valueH = 60 * (2 + ((b - r) / delta));
    }
    else if (max == b)
    {
        valueH = 60 * (4 + ((r - g) / delta));
    }
    if (valueH < 0)
    {
        valueH += 360;
    }
}

void MyWidget::changesOnImage()
{
    for(int y = 0; y < image->height(); y++)
    {
        for (int x = 0; x < image->width(); x++)
        {
            QColor color = getPixelColorAtImage(image, x, y);
            color.getRgb(&red, &green, &blue);
            RGBtoHSV();
            if (valueH <= 0)
            {
                valueH += 360;
            }
            valueH += sliderValueH;
            valueS += sliderValueS;
            valueV += sliderValueV;
            if (valueH > 360)
            {
                valueH -= 360;
            }
            else if (valueH < 0)
            {
                valueH += 360;
            }
            if (valueS > 1)
            {
                valueS = 1;
            }
            else if (valueS < 0)
            {
                valueS = 0;
            }
            if (valueV > 1)
            {
                valueV = 1;
            }
            else if (valueV < 0)
            {
                valueV = 0;
            }
            HSVtoRGB();
            if (red < 0)
                red = 0;
            else if (green < 0)
                green = 0;
            else if (blue < 0 )
                blue = 0;
            color.setRgb(red, green, blue);
            imageToWork.setPixelColor(x, y, color);
        }
    }
    update();
}

void MyWidget::HSVtoRGB()
{
    double c = valueV * valueS;
    double primH = valueH / 60.0;
    double x = c * (1.0 - fabs(fmod(primH, 2) - 1.0));
    double r, g, b;
    if (0 <= primH && primH <= 1)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if (1 < primH && primH <= 2)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if (2 < primH && primH <= 3)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if (3 < primH && primH <= 4)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if (4 < primH && primH <= 5)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }
    double m = valueV - c;
    red = abs(int((r + m) * 255));
    green = abs(int((g + m) * 255));
    blue = abs(int((b + m) * 255));
}

void MyWidget::combineLayers()
{
    imageToWorkAlphaBlending = alphaImages[0];
    QColor tmp;
    for(int y = 0; y < im.height(); y++)
    {
        for (int x = 0; x < im.width(); x++)
        {
            QColor bgColor = blend(getPixelColorAtImage(&imageToWorkAlphaBlending, x ,y), getPixelColorAtImage(&alphaImages[1], x , y), layoutValues[0]);
            imageToWorkAlphaBlending.setPixelColor(x, y, bgColor);
            QColor color = alphaMode(bgColor, &alphaImages[2], x, y);
            imageToWorkAlphaBlending.setPixelColor(x, y, color);
            bgColor = blend(getPixelColorAtImage(&imageToWorkAlphaBlending, x ,y), bgColor, layoutValues[1]);
            imageToWorkAlphaBlending.setPixelColor(x, y, bgColor);
            color = alphaMode(bgColor, &alphaImages[3], x, y);
            imageToWorkAlphaBlending.setPixelColor(x, y, color);
            bgColor = blend(getPixelColorAtImage(&imageToWorkAlphaBlending, x ,y), bgColor, layoutValues[2]);
            imageToWorkAlphaBlending.setPixelColor(x, y, bgColor);
        }
    }
    update();
}

QColor MyWidget::alphaMode(QColor bg, QImage *im2, int x, int y)
{
    int r1, g1, b1, r2, g2, b2, r, g, b;
    QColor color;
    bg.getRgb(&r1, &g1, &b1);
    QColor color2 = getPixelColorAtImage(im2, x, y);
    color2.getRgb(&r2, &g2, &b2);
    if (alphaBlendingMode == "Normal mode")
    {
        return color2;
    }
    else if (alphaBlendingMode == "Multiply mode")
    {
        r = (r1 * r2) >> 8;
        g = (g1 * g2) >> 8;
        b = (b1 * b2) >> 8;
        color.setRgb(r, g, b);
        return color;
    }
    else if (alphaBlendingMode == "Screen mode")
    {
        r = 255 - ((255 - r1) * (255 - r2) >> 8);
        g = 255 - ((255 - g1) * (255 - g2) >> 8);
        b = 255 - ((255 - b1) * (255 - b2) >> 8);
        color.setRgb(r, g, b);
        return color;
    }
    else if (alphaBlendingMode == "Overlay mode")
    {
        if (r1 < 128)
        {
            r = (r1 * r2) >> 7;
        }
        else
        {
            r = 255 - ((255 - r1) * (255 - r2) >> 7);
        }
        if (g1 < 128)
        {
            g = (g1 * g2) >> 7;
        }
        else
        {
            g = 255 - ((255 - g1) * (255 - g2) >> 7);
        }
        if (b1 < 128)
        {
            b = (b1 * b2) >> 7;
        }
        else
        {
            b = 255 - ((255 - b1) * (255 - b2) >> 7);
        }
        color.setRgb(r, g, b);
        return color;
    }
    else if (alphaBlendingMode == "Darken mode")
    {
        if (r1 < r2)
        {
            r = r1;
        }
        else
        {
            r = r2;
        }
        if (g1 < g2)
        {
            g = g1;
        }
        else
        {
            g = g2;
        }
        if (b1 < b2)
        {
            b = b1;
        }
        else
        {
            b = b2;
        }
        color.setRgb(r, g, b);
        return color;
    }
    else if (alphaBlendingMode == "Lighten mode")
    {
        if (r1 > r2)
        {
            r = r1;
        }
        else
        {
            r = r2;
        }
        if (g1 > g2)
        {
            g = g1;
        }
        else
        {
            g = g2;
        }
        if (b1 > b2)
        {
            b = b1;
        }
        else
        {
            b = b2;
        }
        color.setRgb(r, g, b);
        return color;
    }
    return color;
}

QColor MyWidget::blend(QColor bg, QColor T, int alpha)
{
    int r1 ,g1, b1, r2, g2, b2, r, g, b;
    QColor color;
    bg.getRgb(&r1, &g1, &b1);
    T.getRgb(&r2, &g2, &b2);
    //r = ((100 - alpha) * r1 + alpha * r2) / 100;
    r = (alpha * r2 + (100 - alpha) * r1) / 100;
    //g = ((100 - alpha) * g1 + alpha * g2) / 100;
    g = (alpha * g2 + (100 - alpha) * g1) / 100;
    //b = ((100 - alpha) * b1 + alpha * b2) / 100;
    b = (alpha * b2 + (100 - alpha) * b1) / 100;
    color.setRgb(r, g, b);
    return color;
}

void MyWidget::fillHouseVector()
{
    points.push_back(QPoint(400, 500));
    points.push_back(QPoint(500, 500));
    points.push_back(QPoint(500, 400));
    points.push_back(QPoint(400, 400));
    points.push_back(QPoint(450, 350));
    transformedPoints = points;
}

void MyWidget::drawHouse()
{
    drawLine(transformedPoints[0].x(), transformedPoints[0].y(), transformedPoints[1].x(), transformedPoints[1].y(), 255, 255, 255);
    drawLine(transformedPoints[1].x(), transformedPoints[1].y(), transformedPoints[2].x(), transformedPoints[2].y(), 255, 255, 255);
    drawLine(transformedPoints[2].x(), transformedPoints[2].y(), transformedPoints[3].x(), transformedPoints[3].y(), 255, 255, 255);
    drawLine(transformedPoints[3].x(), transformedPoints[3].y(), transformedPoints[0].x(), transformedPoints[0].y(), 255, 255, 255);
    drawLine(transformedPoints[3].x(), transformedPoints[3].y(), transformedPoints[4].x(), transformedPoints[4].y(), 255, 255, 255);
    drawLine(transformedPoints[4].x(), transformedPoints[4].y(), transformedPoints[2].x(), transformedPoints[2].y(), 255, 255, 255);
}

void MyWidget::transformation()
{
    mat T = translation();
    mat T1 = translation(450, 450);
    mat T2 = translation(-450, -450);
    mat S = scalings();
    mat R = rotations();
    mat Sh = shearing();
    //mat M = inv(T1 * T * R * Sh * S * T2);
    //mat M = T1 * T * R * Sh * S * T2;
    mat M = T1 * T * R * Sh * S * T2;
    for (int i = 0; i <= 4; i++)
    {
        mat P (3, 1, fill::ones);
        P(0, 0) = points[i].x();
        P(1, 0) = points[i].y();
        qDebug("OLD: X: %d, Y: %d", points[i].x(), points[i].y());
        mat result = M * P;
        int x = int(result(0, 0));
        int y = int(result(1, 0));
        qDebug("NEW: X: %d, Y: %d", x, y);
        QPoint point(x, y);
        transformedPoints[i] = point;
    }
    update();
}

mat MyWidget::translation()
{
    mat T(3, 3, fill::eye);
    T(0, 2) = translationX;
    T(1, 2) = translationY;
    return T;
}

mat MyWidget::translation(int x, int y)
{
    mat T(3, 3, fill::eye);
    T(0, 2) = x;
    T(1, 2) = y;
    return T;
}

mat MyWidget::scalings()
{
    mat S(3, 3, fill::eye);
    S(0, 0) = double(scalingX) / 100.0;
    S(1, 1) = double(scalingY) / 100.0;
    return S;
}

mat MyWidget::rotations()
{
    double radians = qDegreesToRadians(double(rotation));
    mat R(3, 3, fill::eye);
    R(0, 0) = R(1, 1) = qCos(radians);
    R(1, 0) = qSin(radians);
    R(0, 1) = -qSin(radians);
    return R;
}

mat MyWidget::shearing()
{
    mat Shx(3, 3, fill::eye);
    Shx(0, 1) = double(shearingX) / 100;
    mat Shy(3, 3, fill::eye);
    Shy(1, 0) = double(shearingY) / 100;
    return Shx * Shy;
}

void MyWidget::dilatation(QImage *image, int r)
{
    QImage prevImage = *image;
    image->fill(Qt::black);
    bool pixelColored = false;
    for (int i = 0; i < image->width(); i++)
    {
        for (int j = 0; j < image->height(); j++)
        {
            for(int k = i-r; k <= i+r; k++)
            {
                if (k < 0 || k >= image->width())
                {
                    continue;
                }
                for (int l = j-r; l <= j+r; l++)
                {
                    if (l < 0 || l >= image->height())
                    {
                        continue;
                    }
                    if(getPixelColorAtImage(&prevImage, k,l) == Qt::white)
                    {
                        putPixelAtImage(image, i, j, 255, 255, 255);
                        pixelColored = true;
                        break;
                    }
                }
                if(pixelColored == true)
                {
                    pixelColored = false;
                    break;
                }
            }
        }
    }
    im = *image;
    update();
}

void MyWidget::erosion(QImage *image, int r)
{
    QImage prevImage = *image;
    image->fill(Qt::white);
    bool pixelColored = false;
    for (int i = 0; i < image->width(); i++)
    {
        for (int j = 0; j < image->height(); j++)
        {
            for(int k = i-r; k <= i+r; k++)
            {
                if (k < 0 || k >= image->width() || k == i)
                {
                    continue;
                }
                for (int l = j-r; l <= j+r; l++)
                {
                    if (l < 0 || l >= image->height() || l == j)
                    {
                        continue;
                    }
                    if(getPixelColorAtImage(&prevImage, k,l) == Qt::black)
                    {
                        putPixelAtImage(image, i, j, 0, 0, 0);
                        pixelColored = true;
                        break;
                    }
                }
                if(pixelColored == true)
                {
                    pixelColored = false;
                    break;
                }
            }
        }
    }
    im = *image;
    update();
}

void MyWidget::open(QImage *image, int r)
{
    erosion(image, r);
    dilatation(image, r);
}

void MyWidget::close(QImage *image, int r)
{
    dilatation(image, r);
    erosion(image, r);
}

void MyWidget::fillScanLineVector()
{
    points.push_back(QPoint(120,400));
    points.push_back(QPoint(120, 160));
    points.push_back(QPoint(60, 80));
    points.push_back(QPoint(210, 80));
    points.push_back(QPoint(210, 160));
    points.push_back(QPoint(330, 160));
    points.push_back(QPoint(330, 80));
    points.push_back(QPoint(540, 80));
    points.push_back(QPoint(455, 160));
    points.push_back(QPoint(590, 245));
    points.push_back(QPoint(465, 420));
    points.push_back(QPoint(300, 510));
    points.push_back(QPoint(305, 400));
    points.push_back(QPoint(190, 490));
}

void MyWidget::drawScanLineFigure()
{
    for (int i = 0; i < points.size(); i++)
    {
        putRect(points[i].x(), points[i].y(), 10, 10, 255, 0, 0);
        if(i != 0)
        {
            drawLine(points[i-1].x(), points[i-1].y(), points[i].x(), points[i].y(), 255, 255, 255);
        }
    }
    drawLine(points[0].x(), points[0].y(), points[points.size()-1].x(), points[points.size()-1].y(), 255, 255, 255);
}

void MyWidget::scanLine()
{
    int yMin = points[0].y();
    int yMax = points[0].y();
    for (int i = 1; i < points.size(); i++)
    {
        if (yMin > points[i].y())
        {
            yMin = points[i].y();
        }
        if (yMax < points[i].y())
        {
            yMax = points[i].y();
        }
    }
    for (int y = yMin; y <= yMax; y++)
    {
        QVector<int> xValues;
        for(int i = 0; i < points.size(); i++)
        {
            int j = (i + 1) % points.size();
            if (((y >= points[i].y()) && (y < points[j].y())) || ((y < points[i].y()) && (y >= points[j].y() )))
            {
                int x = int(points[i].x() + ((float((points[j].x() - points[i].x())) / (points[j].y() - points[i].y())) * (y - points[i].y())));
                xValues.push_back(x);
            }
        }
        std::sort(xValues.begin(), xValues.end());
        for (int i = 0; i < xValues.size()-1; i+=2)
        {
            drawLine(xValues[i], y, xValues[i + 1], y, 255, 255, 255);
        }
    }
}

void MyWidget::setChoice(QString what)
{
    choice = what;
    update();
}

void MyWidget::setBeta(int x)
{
    beta = x;
    im.fill(Qt::black);
    drawEllipse(x0, y0, int(R1), int(R2), beta, 255, 255, 255);
}

void MyWidget::setH(int x)
{
    sliderValueH = x;
    changesOnImage();
}

void MyWidget::setS(int x)
{
    sliderValueS = x / 100.0;
    changesOnImage();
}

void MyWidget::setV(int x)
{
    sliderValueV = x / 100.0;
    changesOnImage();
}

void MyWidget::setRForMorficOperation(int x)
{
    rForMorficOperation = x;
}

void MyWidget::setAlphaBlendingMode(QString which)
{
    alphaBlendingMode = which;
    combineLayers();
}

void MyWidget::setAlphaBlendingLayoutFirstValue(int x)
{
    layoutValues[0] = x;
    combineLayers();
}

void MyWidget::setAlphaBlendingLayoutSecondValue(int x)
{
    layoutValues[1] = abs(x);
    combineLayers();
}

void MyWidget::setAlphaBlendingLayoutThirdValue(int x)
{
    layoutValues[2] = abs(x);
    combineLayers();
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

void MyWidget::setYScaling(int x)
{
    scalingY = x;
    transformation();
}

void MyWidget::setXScaling(int x)
{
    scalingX = x;
    transformation();
}

void MyWidget::setRotation(int x)
{
    rotation = x;
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


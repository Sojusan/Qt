#include "mywidget.h"

#include <QColorDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <qmath.h>
#include <algorithm>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent), im(1000, 600, QImage::Format_RGB888)
{

}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //p.drawImage(0, 0, im);
    if (choice == "RGB/HSV")
    {
        p.drawImage(0, 0, imageToWork);
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
                for (unsigned long i = 0; i < points.size(); i++)
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
    unsigned long howMany;
    for (unsigned long i = 0; i < points.size(); i++)
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
        howMany = unsigned(1 + (numberOfPoints - 4)/3);
    }
    for (unsigned long i = 0; i < howMany; i++)
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
    for (unsigned long i = 0; i < points.size(); i++)
    {
        putRect(points[i].x(), points[i].y(), 10, 10, 255, 0, 0);
    }
    for (unsigned long i = 0; i < howMany; i++)
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
    for (unsigned long i = 0; i < points.size(); i++)
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
    for (unsigned long i = 0; i < points.size(); i++)
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
    for (unsigned long i = 1; i < points.size(); i++)
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
        for(unsigned long i = 0; i < points.size(); i++)
        {
            unsigned long j = (i + 1) % points.size();
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


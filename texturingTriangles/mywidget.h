#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QStack>
#include <QWidget>
#include <armadillo>

using namespace arma;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    QImage im;
    QImage *image = new QImage("/home/rgrzegorczyk/Documents/Studia/Qt_creator/texturingTriangles/face_big.jpg");
    QImage *imageToWork = new QImage("/home/rgrzegorczyk/Documents/Studia/Qt_creator/texturingTriangles/face_big.jpg");
    QVector<QPoint> drawVector;
    QVector<QPoint> imageVector;
    QPoint foundPoint;
    double denominator;

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void putPixel(int, int, int, int, int);
    void putPixelAtImage(QImage *im, int x, int y, int r, int g, int b);
    void putRect(int, int, int, int, int, int, int);
    void putRectAtImage(QImage *image, int, int, int, int, int, int, int);
    void drawLine(int, int, int, int, int, int, int);
    void drawDrawTriangle();
    void drawImageTriangle();
    QPoint findClosestPoint(QPoint p, QVector<QPoint> vector);
    void scanLine();

private:

signals:

public slots:

};

#endif // MYWIDGET_H

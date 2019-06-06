#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QStack>
#include <QWidget>
#include <armadillo>
#include <QVector3D>

using namespace arma;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    QImage im;

    QVector<QVector3D> points3D;
    QVector<QVector3D> pointsToDraw;
    QVector<QVector3D> transformedPoints3D;
    int focal = 600;

protected:
    void paintEvent(QPaintEvent *);
    void putPixel(int, int, int, int, int);
    void putPixelAtImage(QImage *im, int x, int y, int r, int g, int b);
    void putRect(int, int, int, int, int, int, int);
    void putRectAtImage(QImage *image, int, int, int, int, int, int, int);
    void drawLine(int, int, int, int, int, int, int);

    void fillCubeVector();
    QVector<QPointF> fillToDrawVector(int focal);
    void drawCube();
    void transformation();
    mat translation();
    mat translation(int x, int y, int z);
    mat scalings();
    mat rotationsX();
    mat rotationsY();
    mat rotationsZ();
    mat shearing();

private:
    int translationX = 0;
    int translationY = 0;
    int translationZ = 0;
    int rotationX = 0;
    int rotationY = 0;
    int rotationZ = 0;
    int scalingX = 100;
    int scalingY = 100;
    int scalingZ = 100;
    int shearingX = 0;
    int shearingY = 0;
    int shearingZ = 0;

signals:

public slots:
    void setXTranslation(int x);
    void setYTranslation(int x);
    void setZTranslation(int x);
    void setXScaling(int x);
    void setYScaling(int x);
    void setZScaling(int x);
    void setXRotation(int x);
    void setYRotation(int x);
    void setZRotation(int x);
    void setXShearing(int x);
    void setYShearing(int x);
    void setZShearing(int x);

};

#endif // MYWIDGET_H

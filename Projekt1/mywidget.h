#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QStack>
#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    QImage im, imPrev;
    QImage* image = new QImage("/home/rgrzegorczyk/Documents/Studia/Qt_creator/hsv/image.jpg");
    QImage imageToWork = *image;
    std::vector<QPoint> points;
    QStack<QPoint> stack;
    unsigned long numberOfPoints = 0;
    bool checked = false;
    int rForMorficOperation = 1;
    void dilatation(QImage *, int);
    void erosion(QImage *, int);
    void open(QImage *, int);
    void close(QImage *, int);
    void scanLine();
    void fillScanLineVector();
    void drawScanLineFigure();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void putPixel(int, int, int, int, int);
    void putPixelAtImage(QImage *im, int x, int y, int r, int g, int b);
    void putRect(int, int, int, int, int, int, int);
    void drawLine(int, int, int, int, int, int, int);
    void drawCircle(int, int, int, int, int, int);
    void drawEllipse(int, int, int, int, float, int, int, int);
    void drawBezierCurve(QPoint, QPoint, QPoint, QPoint, int, int, int);
    void drawWholeBezierCurve(int, int, int);
    void drawSplineCurve(QPoint, QPoint, QPoint, QPoint, int, int, int);
    void drawWholeSplineCurve(int, int, int);
    bool inBordersOfImage(int, int);
    bool inBordersAtImage(QImage *im, int x, int y);
    QColor getPixelColor(int, int);
    QColor getPixelColorAtImage(QImage *, int, int);
    void floodFill(int, int, QColor);
    QPoint findClosestPoint(QPoint);
    void RGBtoHSV();
    void changesOnImage();
    void HSVtoRGB();

private:
    int beta = 0;
    double valueH = 0;
    double valueS = 0;
    double valueV = 0;
    int red = 0;
    int green = 0;
    int blue = 0;
    double sliderValueH = 0;
    double sliderValueS = 0;
    double sliderValueV = 0;
    int startX, startY;
    int x0, y0;
    float R, R1, R2;
    QString choice;
    bool pointMovement = false;
    QPoint foundPoint;

signals:

public slots:
    void setChoice(QString what);
    void setBeta(int x);
    void setH(int x);
    void setS(int x);
    void setV(int x);
    void setRForMorficOperation(int x);
};

#endif // MYWIDGET_H

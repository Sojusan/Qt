#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    QImage im;
    std::vector<QPoint> points;

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void putPixel(int, int, int, int, int);
    void putRect(int, int, int, int, int, int, int);
    void drawLine(int, int, int, int, int, int, int);
    void drawCircle(int, int, int, int, int, int);
    void drawEllipse(int, int, int, int, float, int, int, int);
    void drawBezierCurve(QPoint, QPoint, QPoint, QPoint, int, int, int);
    void drawWholeBezierCurve(int, int, int);
    void drawSplineCurve(QPoint, QPoint, QPoint, QPoint, int, int, int);
    void drawWholeSplineCurve(int, int, int);
    QPoint findClosestPoint(QPoint);

private:
    int numberOfPoints = 0;
    int beta = 0;
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
};

#endif // MYWIDGET_H

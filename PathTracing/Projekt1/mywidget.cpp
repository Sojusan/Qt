#include "mywidget.h"

#include <QColorDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <qmath.h>
#include <QtMath>
#include <algorithm>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent), im(900, 600, QImage::Format_RGB888)
{
    //test();
    //betterTest();
    //anotherTest();
    cameraTest();
}


void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
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
        //update();
    }
}

void MyWidget::test()
{
    int nx = 900;
    int ny = 450;

    //Camera cam(90, 2);
    Hitable *list[2];
    list[0] = new Sphere(QVector3D(0, 0, -1), 0.5, new Lambertian(QVector3D(0.8f, 0.3f, 0.3f)));
    list[1] = new Sphere(QVector3D(0, -100.5, -1), 100, new Lambertian(QVector3D(0.8f, 0.8f, 0.0f)));
    Hitable *world = new HitableList(list, 2);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
        //    Ray ray = cam.getRay(u, v);
      //      QVector3D p = ray.getPointAtRay(2.0);
      //      QVector3D col = color(ray, world, 0);

        //    col = QVector3D(sqrtf(col[0]), sqrtf(col[1]), sqrtf(col[2]));
        //    int ir = int(255 * col[0]);
        //    int ig = int(255 * col[1]);
        //    int ib = int(255 * col[2]);

//            putPixel(i, j, ir, ig, ib);
        }
    }
}

void MyWidget::betterTest()
{
    int nx = 900;
    int ny = 450;
    int ns = 100;

    //Camera cam(90, 2);
    Hitable *list[2];
    list[0] = new Sphere(QVector3D(0, 0, -1), 0.5, new Lambertian(QVector3D(0.8f, 0.3f, 0.3f)));
    list[1] = new Sphere(QVector3D(0, -100.5, -1), 100, new Lambertian(QVector3D(0.8f, 0.8f, 0.0f)));
    Hitable *world = new HitableList(list, 2);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            QVector3D col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                //Ray ray = cam.getRay(u, v);
                //QVector3D p = ray.getPointAtRay(2.0);
                //col += color(ray, world, 1);
            }
            col /= float(ns);
            col = QVector3D(sqrtf(col[0]), sqrtf(col[1]), sqrtf(col[2]));
            int ir = int(255 * col[0]);
            int ig = int(255 * col[1]);
            int ib = int(255 * col[2]);

            putPixel(i, j, ir, ig, ib);
        }
    }
}

void MyWidget::anotherTest()
{
    int nx = 900;
    int ny = 450;
    int ns = 100;
    //Hitable *list[5];
    /*
    list[0] = new Sphere(QVector3D(0, 0, -1), 0.5, new Lambertian(QVector3D(0.8f, 0.3f, 0.3f)));
    list[1] = new Sphere(QVector3D(0, -100.5, -1), 100, new Lambertian(QVector3D(0.8f, 0.8f, 0.0f)));
    list[2] = new Sphere(QVector3D(1, 0, -1), 0.5, new Metal(QVector3D(0.8f, 0.6f, 0.2f), 0.3f));
    list[3] = new Sphere(QVector3D(-1, 0, -1), 0.5, new Metal(QVector3D(0.8f, 0.8f, 0.8f), 1.0f));
    */
    //list[0] = new Sphere(QVector3D(0, 0, -1), 0.5, new Lambertian(QVector3D(0.1f, 0.2f, 0.5f)));
    //list[1] = new Sphere(QVector3D(0, -100.5, -1), 100, new Lambertian(QVector3D(0.8f, 0.8f, 0.0f)));
    //list[2] = new Sphere(QVector3D(-1, 0, -1), 0.5, new Metal(QVector3D(0.8f, 0.6f, 0.2f), 1.0f));
    //list[3] = new Sphere(QVector3D(1, 0, -1), 0.5, new Dielectric(1.5));
    //list[4] = new Sphere(QVector3D(1, 0, -1), -0.45f, new Dielectric(1.5));
   // float R = cosf(float(M_PI) / 4);
   // list[0] = new Sphere(QVector3D(-R, 0, -1), R, new Lambertian(QVector3D(0, 0, 1)));
   // list[1] = new Sphere(QVector3D(R, 0, -1), R , new Lambertian(QVector3D(1, 0, 0)));
    //Hitable *world = new HitableList(list, 5);
    Hitable *world = simpleLight();
    //Camera cam(QVector3D(2, 2, 1), QVector3D(0, 0, -1), QVector3D(0, -1, 0), 90, float(nx) / float(ny));
    Camera cam(QVector3D(9, 2, 1), QVector3D(3, 1, 3), QVector3D(0, -1, 0), 90, float(nx) / float(ny));
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            QVector3D col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                Ray ray = cam.getRay(u, v);
                col += color(ray, world, 0);
            }
            col /= float(ns);
            col = QVector3D(sqrtf(col[0]), sqrtf(col[1]), sqrtf(col[2]));
            int ir = int(255 * col[0]);
            int ig = int(255 * col[1]);
            int ib = int(255 * col[2]);

            putPixel(i, j, ir, ig, ib);
        }
    }
}

void MyWidget::generate(int x, int y, int z, int x2, int y2, int z2, int x3, int y3, int z3)
{
    int nx = 900;
    int ny = 450;
    int ns = 10000;
    //Hitable *list[5];
    /*
    list[0] = new Sphere(QVector3D(0, 0, -1), 0.5, new Lambertian(QVector3D(0.8f, 0.3f, 0.3f)));
    list[1] = new Sphere(QVector3D(0, -100.5, -1), 100, new Lambertian(QVector3D(0.8f, 0.8f, 0.0f)));
    list[2] = new Sphere(QVector3D(1, 0, -1), 0.5, new Metal(QVector3D(0.8f, 0.6f, 0.2f), 0.3f));
    list[3] = new Sphere(QVector3D(-1, 0, -1), 0.5, new Metal(QVector3D(0.8f, 0.8f, 0.8f), 1.0f));
    */
    //list[0] = new Sphere(QVector3D(0, 0, -1), 0.5, new Lambertian(QVector3D(0.1f, 0.2f, 0.5f)));
    //list[1] = new Sphere(QVector3D(0, -100.5, -1), 100, new Lambertian(QVector3D(0.8f, 0.8f, 0.0f)));
    //list[2] = new Sphere(QVector3D(-1, 0, -1), 0.5, new Metal(QVector3D(0.8f, 0.6f, 0.2f), 1.0f));
    //list[3] = new Sphere(QVector3D(1, 0, -1), 0.5, new Dielectric(1.5));
    //list[4] = new Sphere(QVector3D(1, 0, -1), -0.45f, new Dielectric(1.5));
   // float R = cosf(float(M_PI) / 4);
   // list[0] = new Sphere(QVector3D(-R, 0, -1), R, new Lambertian(QVector3D(0, 0, 1)));
   // list[1] = new Sphere(QVector3D(R, 0, -1), R , new Lambertian(QVector3D(1, 0, 0)));
    //Hitable *world = new HitableList(list, 5);
    //Hitable *world = simpleLight();
    //Camera cam(QVector3D(2, 2, 1), QVector3D(0, 0, -1), QVector3D(0, -1, 0), 90, float(nx) / float(ny));
    Camera cam(QVector3D(x, y, z), QVector3D(x2, y2, z2), QVector3D(x3, y3, z3), 40.0f, float(nx) / float(ny));
    Hitable *world = cornellBox();
    //QVector3D lookfrom(278, 278, -800);
    //QVector3D lookat(278, 278, 0);
    //float vfov = 40.0f;
    //Camera cam(QVector3D(6, 2, -2), QVector3D(-1, -1, -1), QVector3D(0, -1, 0), 90, float(nx) / float(ny));
    //Camera cam(lookfrom, lookat, QVector3D(0, -1, 0), vfov, float(nx) / float(ny));

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            QVector3D col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                Ray ray = cam.getRay(u, v);
                col += color(ray, world, 0);
            }
            col /= float(ns);
            col = QVector3D(sqrtf(col[0]), sqrtf(col[1]), sqrtf(col[2]));
            int ir = int(255 * col[0]);
            int ig = int(255 * col[1]);
            int ib = int(255 * col[2]);

            putPixel(i, j, ir, ig, ib);
        }
    }
    update();
}

void MyWidget::cameraTest()
{
    int nx = 900;
    int ny = 450;
    //Hitable *list[5];

    //list[0] = new Sphere(QVector3D(0, 0, -1), 0.5, new Lambertian(QVector3D(0.1f, 0.2f, 0.5f)));
    //list[1] = new Sphere(QVector3D(0, -100.5, -1), 100, new Lambertian(QVector3D(0.8f, 0.8f, 0.0f)));
    //list[2] = new Sphere(QVector3D(-1, 0, -1), 0.5, new Metal(QVector3D(0.8f, 0.6f, 0.2f), 1.0f));
    //list[3] = new Sphere(QVector3D(1, 0, -1), 0.5, new Dielectric(1.5));
    //list[4] = new Sphere(QVector3D(1, 0, -1), -0.45f, new Dielectric(1.5));
    //Hitable *world = new HitableList(list, 5);
    //Hitable *world = simpleLight();
    Hitable *world = cornellBox();
    QVector3D lookfrom(278, 278, -800);
    QVector3D lookat(278, 278, 0);
    float vfov = 40.0f;
    //Camera cam(QVector3D(6, 2, -2), QVector3D(-1, -1, -1), QVector3D(0, -1, 0), 90, float(nx) / float(ny));
    Camera cam(lookfrom, lookat, QVector3D(0, -1, 0), vfov, float(nx) / float(ny));
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            //QVector3D col(0, 0, 0);
            //for (int s = 0; s < ns; s++) {
            //    float u = float(i + drand48()) / float(nx);
            //    float v = float(j + drand48()) / float(ny);
            //    Ray ray = cam.getRay(u, v);
                //QVector3D p = ray.getPointAtRay(2.0);
            //    col += color(ray, world, 0);
            //}
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray ray = cam.getRay(u, v);
            //col /= float(ns);
            //col = QVector3D(sqrtf(col[0]), sqrtf(col[1]), sqrtf(col[2]));
            QVector3D col = color(ray, world, 0);
            int ir = int(255 * col[0]);
            int ig = int(255 * col[1]);
            int ib = int(255 * col[2]);

            putPixel(i, j, ir, ig, ib);
        }
    }
}

void MyWidget::cameraTest(int x, int y, int z, int x2, int y2, int z2, int x3, int y3, int z3)
{
    int nx = 900;
    int ny = 450;
    Hitable *world = cornellBox();
    Camera cam(QVector3D(x, y, z), QVector3D(x2, y2, z2), QVector3D(x3, y3, z3), 40.0f, float(nx) / float(ny));
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray ray = cam.getRay(u, v);
            QVector3D col = color(ray, world, 0);
            int ir = int(255 * col[0]);
            int ig = int(255 * col[1]);
            int ib = int(255 * col[2]);

            putPixel(i, j, ir, ig, ib);
        }
    }
    update();
}


QVector3D MyWidget::color(const Ray &ray, Hitable *world, int depth)
{
    hitRecord rec;
    if (world->hit(ray, 0.001f, MAXFLOAT, rec)) {
        Ray scattered;
        QVector3D attenuation;
        QVector3D emitted = rec.matPtr->emitted(rec.u, rec.v, rec.p);
        if (depth < 50 && rec.matPtr->scatter(ray, rec.p, rec.normal, attenuation, scattered)) {
            return emitted + attenuation * color(scattered, world, depth+1);
        }
        else {
            return emitted;
        }
    }
    else {
        return QVector3D(0, 0, 0);
        //ray.direction().normalize();
        //float t = 0.5f * (ray.direction().y() + 1.0f);
        //return (1.0f - t) * QVector3D(1.0, 1.0, 1.0) + t * QVector3D(0.5, 0.7f, 1.0);
    }
}
/*
QVector3D MyWidget::color(const Ray &ray, Hitable *world, int depth)
{
    hitRecord rec;
    if (world->hit(ray, 0.001f, MAXFLOAT, rec)) {
        Ray scattered;
        QVector3D attenuation;
        if (depth < 50 && rec.matPtr->scatter(ray, rec.p, rec.normal, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth+1);
        }
        else {
            return QVector3D(0, 0, 0);
        }
    }
    else {
        ray.direction().normalize();
        float t = 0.5f * (ray.direction().y() + 1.0f);
        return (1.0f - t) * QVector3D(1.0, 1.0, 1.0) + t * QVector3D(0.5, 0.7f, 1.0);
    }
}
*/

QVector3D MyWidget::randomInUnitSphere()
{
    QVector3D p;
    do {
        p = 2.0 * QVector3D(float(drand48()), float(drand48()), float(drand48())) - QVector3D(1, 1, 1);
    } while (p.lengthSquared() >= 1.0f);
    return p;
}

Hitable *MyWidget::randomScene()
{
    int n = 500;
    Hitable **list = new Hitable*[n+1];
    list[0] = new Sphere(QVector3D(0, -1000, 0), 1000, new Lambertian(QVector3D(0.5f, 0.5f, 0.5f)));
    int i = 1;
    /*for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float chooseMat = float(drand48());
            QVector3D center(a + 0.9f * float(drand48()), 0.2f, b + 0.9f * float(drand48()));
            if ((center - QVector3D(4, 0.2f, 0)).length() > 0.9f) {
                if (chooseMat < 0.8f) { //diffuse
                    list[i++] = new Sphere(center, 0.2f, new Lambertian(QVector3D(float(drand48())*float(drand48()), float(drand48())*float(drand48()), float(drand48())*float(drand48()))));
                }
                else if (chooseMat < 0.95f) { //metal
                    list[i++] = new Sphere(center, 0.2f, new Metal(QVector3D(0.5f * (1 + float(drand48())), 0.5f*(1 + float(drand48())), 0.5f * (1 + float(drand48()))), 0.5f * float(drand48())));
                }
                else { //glass
                    list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5));
                }
            }
        }
    }*/
    list[i++] = new Sphere(QVector3D(0, 1, 0), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(QVector3D(-4, 1, 0), 1.0, new Lambertian(QVector3D(0.4f, 0.2f, 0.1f)));
    list[i++] = new Sphere(QVector3D(4, 1, 0), 1.0, new Metal(QVector3D(0.7f, 0.6f, 0.5f), 0.0));

    return new HitableList(list, i);
}

Hitable *MyWidget::simpleLight()
{
    Hitable **list = new Hitable*[4];
    //list[0] = new Sphere(QVector3D(0, -1000, 0), 1000, new Lambertian(QVector3D(0.4f, 0.2f, 0.1f)));
    list[0] = new xyRect(3, 5, 1, 3, -2, new Lambertian(QVector3D(0.4f, 0.2f, 0.1f)));
    list[1] = new Sphere(QVector3D(0, 3, 0), 2, new Lambertian(QVector3D(0.4f, 0.2f, 0.1f)));
    //list[2] = new Plane(3, 5, 1, 3, -2, new DiffuseLight(new ConstantTexture(QVector3D(4, 4, 4))));
    list[3] = new Sphere(QVector3D(5, 2, 0), 2, new Metal(QVector3D(0.4f, 0.2f, 0.1f), 0.0f));
    list[2] = new Sphere(QVector3D(0, 4, 5), 2, new DiffuseLight(new ConstantTexture(QVector3D(4, 4, 4))));
    //list[3] = new Sphere(QVector3D(0, 7, 0), 2, new DiffuseLight(new ConstantTexture(QVector3D(4, 4, 4))));
    return new HitableList(list, 4);
}

Hitable *MyWidget::cornellBox()
{
    Hitable **list = new Hitable*[10];
    int i = 0;
    Material *red = new Lambertian(QVector3D(0.65f, 0.05f, 0.05f));
    Material *white = new Lambertian(QVector3D(0.73f, 0.73f, 0.73f));
    Material *green = new Lambertian(QVector3D(0.12f, 0.45f, 0.15f));
    Material *light = new DiffuseLight(new ConstantTexture(QVector3D(4, 4, 4)));
    list[i++] = new FlipNormals(new yzRect(0, 555, 0, 555, 555, red));
    list[i++] = new yzRect(0, 555, 0, 555, 0, green);
    list[i++] = new xzRect(113, 443, 127, 432, 554, light);
    list[i++] = new FlipNormals(new xzRect(0, 555, 0, 555, 555, white));
    list[i++] = new xzRect(0, 555, 0, 555, 0, white);
    list[i++] = new FlipNormals(new xyRect(0, 555, 0, 555, 555, white));
    //list[i++] = new Sphere(QVector3D(270, 225, 400), 100, new Lambertian(QVector3D(0.4f, 0.2f, 0.1f)));
    list[i++] = new Sphere(QVector3D(270, 225, 400), 100, new Dielectric(0.0f));
    list[i++] = new Sphere(QVector3D(100, 175, 300), 75, new Metal(QVector3D(0.53f, 0.14f, 0.39f), 1.0f));
    list[i++] = new Sphere(QVector3D(440, 175, 300), 75, new Dielectric(1.5f));
    list[i++] = new Sphere(QVector3D(270, 100, 200), 50, new Lambertian(QVector3D(0.4f, 0.2f, 0.1f)));
    return new HitableList(list, i);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->translationXSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setXTranslation(int)));
    connect(ui->translationYSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setYTranslation(int)));
    connect(ui->translationZSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setZTranslation(int)));
    connect(ui->rotationXSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setXRotation(int)));
    connect(ui->rotationYSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setYRotation(int)));
    connect(ui->rotationZSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setZRotation(int)));
    connect(ui->scalingXSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setXScaling(int)));
    connect(ui->scalingYSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setYScaling(int)));
    connect(ui->scalingZSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setZScaling(int)));
    connect(ui->shearingXSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setXShearing(int)));
    connect(ui->shearingYSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setYShearing(int)));
    connect(ui->shearingZSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setZShearing(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

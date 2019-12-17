#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->goButton, SIGNAL(clicked()), this, SLOT(cameraMove()));
    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(generate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cameraMove()
{
    ui->ekran->cameraTest(ui->positionX->value(), ui->positionY->value(), ui->positionZ->value(), ui->positionX_2->value(), ui->positionY_2->value(), ui->positionZ_2->value(), ui->positionX_3->value(), ui->positionY_3->value(), ui->positionZ_3->value());
}

void MainWindow::generate()
{
    ui->ekran->generate(ui->positionX->value(), ui->positionY->value(), ui->positionZ->value(), ui->positionX_2->value(), ui->positionY_2->value(), ui->positionZ_2->value(), ui->positionX_3->value(), ui->positionY_3->value(), ui->positionZ_3->value());
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->obrotSlider->hide();

    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(whatToDraw()));
    connect(ui->obrotSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setBeta(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::whatToDraw()
{
    ui->obrotSlider->hide();
    if (ui->comboBox->currentText() == "Elipsa")
    {
        ui->obrotSlider->show();
    }
    ui->ekran->setChoice(ui->comboBox->currentText());
}

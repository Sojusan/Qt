#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->obrotSlider->hide();
    ui->openButton->hide();
    ui->closeButton->hide();
    ui->erosionButton->hide();
    ui->dilatationButton->hide();
    ui->rLabel->hide();
    ui->valueOfRBox->hide();
    ui->dHLabel->hide();
    ui->dSLabel->hide();
    ui->dVLabel->hide();
    ui->dHSlider->hide();
    ui->dSSlider->hide();
    ui->dVSlider->hide();

    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(whatToDraw()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ui->fillCheckBox, SIGNAL(clicked()), this, SLOT(checkMode()));
    connect(ui->obrotSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setBeta(int)));
    connect(ui->valueOfRBox, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setRForMorficOperation(int)));
    connect(ui->dilatationButton, SIGNAL(clicked()), this, SLOT(dilatationUse()));
    connect(ui->erosionButton, SIGNAL(clicked()), this, SLOT(erosionUse()));
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openUse()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeUse()));
    connect(ui->drawFigureButton, SIGNAL(clicked()), this, SLOT(drawFigure()));
    connect(ui->scanLineButton, SIGNAL(clicked()), this, SLOT(scanLine()));
    connect(ui->dHSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setH(int)));
    connect(ui->dSSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setS(int)));
    connect(ui->dVSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setV(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::whatToDraw()
{
    ui->obrotSlider->hide();
    ui->openButton->hide();
    ui->closeButton->hide();
    ui->erosionButton->hide();
    ui->dilatationButton->hide();
    ui->rLabel->hide();
    ui->valueOfRBox->hide();
    ui->dHLabel->hide();
    ui->dSLabel->hide();
    ui->dVLabel->hide();
    ui->dHSlider->hide();
    ui->dSSlider->hide();
    ui->dVSlider->hide();
    if (ui->comboBox->currentText() == "Elipsa")
    {
        ui->obrotSlider->show();
    }
    if (ui->comboBox->currentText() == "Operacje morfologiczne")
    {
        ui->openButton->show();
        ui->closeButton->show();
        ui->erosionButton->show();
        ui->dilatationButton->show();
        ui->rLabel->show();
        ui->valueOfRBox->show();
    }
    if (ui->comboBox->currentText() == "RGB/HSV")
    {
        ui->dHLabel->show();
        ui->dSLabel->show();
        ui->dVLabel->show();
        ui->dHSlider->show();
        ui->dSSlider->show();
        ui->dVSlider->show();
    }
    ui->ekran->setChoice(ui->comboBox->currentText());
}

void MainWindow::checkMode()
{
    if(ui->ekran->checked == false)
    {
        ui->ekran->checked = true;
    }
    else
    {
        ui->ekran->checked = false;
    }
}

void MainWindow::clearAll()
{
    ui->ekran->im.fill(Qt::black);
    ui->ekran->points.clear();
    ui->ekran->numberOfPoints = 0;
    ui->ekran->update();
}

void MainWindow::dilatationUse()
{
    ui->ekran->dilatation(&(ui->ekran->im), ui->ekran->rForMorficOperation);
}

void MainWindow::erosionUse()
{
    ui->ekran->erosion(&(ui->ekran->im), ui->ekran->rForMorficOperation);
}

void MainWindow::openUse()
{
    ui->ekran->open(&(ui->ekran->im), ui->ekran->rForMorficOperation);
}

void MainWindow::closeUse()
{
    ui->ekran->close(&(ui->ekran->im), ui->ekran->rForMorficOperation);
}

void MainWindow::scanLine()
{
    ui->comboBox->setCurrentIndex(5);
    ui->ekran->setChoice(ui->comboBox->currentText());
    ui->ekran->scanLine();
}

void MainWindow::drawFigure()
{
    ui->ekran->fillScanLineVector();
    ui->ekran->drawScanLineFigure();
}


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
    ui->alphaBlendingComboBox->hide();
    ui->alphaBlendingConfirmButton->hide();
    ui->layoutFirstLabel->hide();
    ui->layoutSecondLabel->hide();
    ui->layoutThirdLabel->hide();
    ui->layoutFirstSlider->hide();
    ui->layoutSecondSlider->hide();
    ui->layoutThirdSlider->hide();
    ui->translationLabel->hide();
    ui->translationXLabel->hide();
    ui->translationYLabel->hide();
    ui->translationXSlider->hide();
    ui->translationYSlider->hide();
    ui->scalingLabel->hide();
    ui->scalingXLabel->hide();
    ui->scalingYLabel->hide();
    ui->scalingXSlider->hide();
    ui->scalingYSlider->hide();
    ui->rotationLabel->hide();
    ui->rotationSlider->hide();
    ui->shearingLabel->hide();
    ui->shearingXLabel->hide();
    ui->shearingYLabel->hide();
    ui->shearingXSlider->hide();
    ui->shearingYSlider->hide();

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
    connect(ui->alphaBlendingConfirmButton, SIGNAL(clicked()), this, SLOT(alphaBlendingMode()));
    connect(ui->layoutFirstSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setAlphaBlendingLayoutFirstValue(int)));
    connect(ui->layoutSecondSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setAlphaBlendingLayoutSecondValue(int)));
    connect(ui->layoutThirdSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setAlphaBlendingLayoutThirdValue(int)));
    connect(ui->translationXSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setXTranslation(int)));
    connect(ui->translationYSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setYTranslation(int)));
    connect(ui->rotationSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setRotation(int)));
    connect(ui->scalingXSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setXScaling(int)));
    connect(ui->scalingYSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setYScaling(int)));
    connect(ui->shearingXSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setXShearing(int)));
    connect(ui->shearingYSlider, SIGNAL(valueChanged(int)), ui->ekran, SLOT(setYShearing(int)));
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
    ui->alphaBlendingComboBox->hide();
    ui->alphaBlendingConfirmButton->hide();
    ui->layoutFirstLabel->hide();
    ui->layoutSecondLabel->hide();
    ui->layoutThirdLabel->hide();
    ui->layoutFirstSlider->hide();
    ui->layoutSecondSlider->hide();
    ui->layoutThirdSlider->hide();
    ui->translationLabel->hide();
    ui->translationXLabel->hide();
    ui->translationYLabel->hide();
    ui->translationXSlider->hide();
    ui->translationYSlider->hide();
    ui->scalingLabel->hide();
    ui->scalingXLabel->hide();
    ui->scalingYLabel->hide();
    ui->scalingXSlider->hide();
    ui->scalingYSlider->hide();
    ui->rotationLabel->hide();
    ui->rotationSlider->hide();
    ui->shearingLabel->hide();
    ui->shearingXLabel->hide();
    ui->shearingYLabel->hide();
    ui->shearingXSlider->hide();
    ui->shearingYSlider->hide();
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
    if (ui->comboBox->currentText() == "Alpha Blending")
    {
        ui->alphaBlendingComboBox->show();
        ui->alphaBlendingConfirmButton->show();
        ui->layoutFirstLabel->show();
        ui->layoutSecondLabel->show();
        ui->layoutThirdLabel->show();
        ui->layoutFirstSlider->show();
        ui->layoutSecondSlider->show();
        ui->layoutThirdSlider->show();
    }
    if (ui->comboBox->currentText() == "Translations2D")
    {
        ui->translationLabel->show();
        ui->translationXLabel->show();
        ui->translationYLabel->show();
        ui->translationXSlider->show();
        ui->translationYSlider->show();
        ui->scalingLabel->show();
        ui->scalingXLabel->show();
        ui->scalingYLabel->show();
        ui->scalingXSlider->show();
        ui->scalingYSlider->show();
        ui->rotationLabel->show();
        ui->rotationSlider->show();
        ui->shearingLabel->show();
        ui->shearingXLabel->show();
        ui->shearingYLabel->show();
        ui->shearingXSlider->show();
        ui->shearingYSlider->show();
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

void MainWindow::alphaBlendingMode()
{
    ui->ekran->setAlphaBlendingMode(ui->alphaBlendingComboBox->currentText());
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void whatToDraw();
    void checkMode();
    void clearAll();
    void dilatationUse();
    void erosionUse();
    void openUse();
    void closeUse();
    void scanLine();
    void drawFigure();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

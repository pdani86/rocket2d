#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <memory>

#include "rocket.h"
#include "rocketgraphics.h"
#include "posveldisplay.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer timer;

    void updateScene();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    Rocket rocket;
    RocketGraphics* rocketGraphics = nullptr;

    std::unique_ptr<PosVelDisplay, std::function<void(PosVelDisplay*)>> posVelWindow;

public slots:
    void timer_timeout();
private slots:
    void on_verticalSlider_valueChanged(int value);
};
#endif // MAINWINDOW_H

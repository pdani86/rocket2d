#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsItemGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&timer, &QTimer::timeout, this, &MainWindow::timer_timeout);
    timer.setInterval(15);
    timer.start();

    ui->graphicsView->scale(1.0, -1.0);
    ui->graphicsView->setScene(&scene);
    scene.addLine(-1.0e12, 0.0, 1.0e12, 0.0);
    auto sceneHalfWidth = 100.0;
    ui->graphicsView->setSceneRect(-sceneHalfWidth, -sceneHalfWidth, sceneHalfWidth*2, sceneHalfWidth*2);

    rocketGraphics = new RocketGraphics();
    scene.addItem(rocketGraphics);

    posVelWindow = decltype(posVelWindow)(new PosVelDisplay(), [](PosVelDisplay*){});
    posVelWindow->show();
    ui->gridLayout_2->addWidget(posVelWindow.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScene() {
    ui->progressBar->setMaximum(rocket.fuelTankCapacity);
    ui->progressBar->setValue(rocket.fuel);
    rocketGraphics->update(rocket);


    Vec2D centerPos = rocket.getCenterOfMassGlobal();

    auto sceneHalfWidth = 100.0;
    ui->graphicsView->setSceneRect(-sceneHalfWidth + centerPos.x, -sceneHalfWidth + centerPos.y, sceneHalfWidth*2, sceneHalfWidth*2);
}

void MainWindow::timer_timeout() {

    if(ui->gravityCheck->isChecked()) {
        rocket.addMomentum(Vec2D(0.0, -9.81f) * 0.015f * rocket.getMass());
    }
    rocket.rotationDampener = ui->rotDampener->isChecked();
    if(ui->turnCCWbtn->isDown()) {
        rocket.turn(1.0);
    } else  if(ui->turnCWbtn->isDown()) {
        rocket.turn(-1.0);
    } else {
        rocket.turn(0.0);
    }

    rocket.iterate(15000);

    updateScene();

    posVelWindow->update(this->rocket);
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    rocket.throttle = ui->verticalSlider->value() / (float)ui->verticalSlider->maximum();
}

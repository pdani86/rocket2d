#include "posveldisplay.h"
#include "ui_posveldisplay.h"

PosVelDisplay::PosVelDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PosVelDisplay)
{
    ui->setupUi(this);
}

PosVelDisplay::~PosVelDisplay()
{
    delete ui;
}

void PosVelDisplay::update(const Rocket& rocket) {
    ui->pX->setText(QString("%1").arg(rocket.pos.x));
    ui->pY->setText(QString("%1").arg(rocket.pos.y));
    ui->vX->setText(QString("%1").arg(rocket.velocity.x));
    ui->vY->setText(QString("%1").arg(rocket.velocity.y));

    ui->orient->setText(QString("%1").arg(180.0f / M_PI * Rocket::clampRad(rocket.orientation - M_PI_2)));
    ui->angVel->setText(QString("%1").arg(180.0f / M_PI * rocket.angular_speed));
}

#ifndef POSVELDISPLAY_H
#define POSVELDISPLAY_H

#include <QWidget>

#include "rocket.h"

namespace Ui {
class PosVelDisplay;
}

class PosVelDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit PosVelDisplay(QWidget *parent = nullptr);
    ~PosVelDisplay();

    void update(const Rocket& rocket);

private:
    Ui::PosVelDisplay *ui;
};

#endif // POSVELDISPLAY_H

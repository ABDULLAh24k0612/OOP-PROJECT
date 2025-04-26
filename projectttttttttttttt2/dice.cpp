#include "dice.h"
#include <QRandomGenerator>

int Dice::roll() {
    return QRandomGenerator::global()->bounded(1, 7);
}

QString Dice::getImagePath(int value) {
    return QString(":/assets/1-6/%1.png").arg(value);
}

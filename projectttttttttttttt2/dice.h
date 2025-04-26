#ifndef DICE_H
#define DICE_H

#include <QString>

class Dice {
public:
    static int roll();
    static QString getImagePath(int value);
};

#endif // DICE_H

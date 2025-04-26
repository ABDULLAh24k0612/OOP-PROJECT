#ifndef BOARD_H
#define BOARD_H

#include <QPoint>

class Board {
public:
    static int applySnakesAndLadders(int position);
    static QPoint getBoardCoordinates(int position, int boardWidth);
};

#endif // BOARD_H

#include "board.h"
#include <QMap>

int Board::applySnakesAndLadders(int position) {
    static QMap<int, int> jumps = {
        {2, 23}, {17, 93}, {8, 12}, {32, 51}, {70, 89}, {75, 96},
        {39, 80}, {62, 78}, {29, 54}, {31, 14}, {41, 20},
        {67, 50}, {99, 4}, {59, 37}, {92, 76}, {82, 61}
    };
    return jumps.value(position, position);
}

QPoint Board::getBoardCoordinates(int position, int boardWidth) {
    int row = (position - 1) / 10;
    int col = (row % 2 == 0) ? (position - 1) % 10 : 9 - ((position - 1) % 10);
    int tileSize = boardWidth / 10;
    int x = col * tileSize + tileSize / 2;
    int y = (9 - row) * tileSize + tileSize / 2;
    return QPoint(x, y);
}

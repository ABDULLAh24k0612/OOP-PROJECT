#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QVBoxLayout>
#include <QGridLayout>
#include "clickablelabel.h"
#include "player.h"

class GamePage : public QWidget {
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);

    void startGame(int totalPlayers);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void rollDice();

private:
    void setupUI();
    void updateDiceImage(int value);
    void movePlayer(int index, int steps);
    void updatePlayerToken(int index);
    void updatePlayerTurnIndicator();
    QPoint getBoardCoordinates(int position);

    QLabel *boardLabel;
    ClickableLabel *diceLabel;
    QVector<QLabel*> playerTokens;
    QVector<QLabel*> playerIcons;
    QPixmap getRoundedPixmap(const QString &path, int size, int radius);

    QVector<Player> players;
    int currentPlayerIndex;
    int totalPlayers;
};

#endif // GAMEPAGE_H

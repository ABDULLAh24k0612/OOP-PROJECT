#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QStackedWidget>
#include "clickablelabel.h"
#include "player.h"
#include "homepage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void setupUI();
    void setupGamePage();
    void updatePlayerCount(int count);
    void startGame();
    void rollDice();
    void updateDiceImage(int value);
    void movePlayer(int index, int steps);
    void updatePlayerToken(int index);
    void updatePlayerTurnIndicator();
    QPixmap getRoundedPixmap(const QString &path, int size, int radius);

    QPoint getBoardCoordinates(int position);

    HomePage *homePage;
    QWidget *gamePage;
    ClickableLabel *diceLabel;
    QLabel *boardLabel;
    QVector<QLabel*> playerTokens;
    QVector<QLabel*> playerIcons;
    QStackedWidget *stack;

    QVector<Player> players;
    int currentPlayerIndex;
    int totalPlayers;
};

#endif // MAINWINDOW_H


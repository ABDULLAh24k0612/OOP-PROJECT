#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "homepage.h"
#include "gamepage.h"

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

private:
    void setupUI();
    void updatePlayerCount(int count);

    HomePage *homePage;
    GamePage *gamePage;
    QStackedWidget *stack;

    int totalPlayers;
};

#endif // MAINWINDOW_H

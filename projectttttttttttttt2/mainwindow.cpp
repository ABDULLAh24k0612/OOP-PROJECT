#include "mainwindow.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), totalPlayers(2) {
    setupUI();
    setFixedSize(1000, 1000);
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap background(":/assets/background1.png");
    painter.drawPixmap(0, 0, width(), height(), background);
}

void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    homePage = new HomePage();
    gamePage = new GamePage();

    stack = new QStackedWidget(this);
    stack->addWidget(homePage);
    stack->addWidget(gamePage);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(stack);

    connect(homePage->getStartButton(), &QPushButton::clicked, this, [=]() {
        stack->setCurrentWidget(gamePage);
        gamePage->startGame(totalPlayers);
    });

    connect(homePage->getSlider(), &QSlider::valueChanged, this, &MainWindow::updatePlayerCount);
}

void MainWindow::updatePlayerCount(int count) {
    totalPlayers = count;
    homePage->getPlayerCountLabel()->setText(QString("Players: %1").arg(count));
}

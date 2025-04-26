#include "homepage.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(50, 100, 50, 50);
    layout->setSpacing(30);

    QLabel *title = new QLabel("Snake and Ladder");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");

    playerSlider = new QSlider(Qt::Horizontal);
    playerSlider->setRange(2, 4);
    playerSlider->setValue(2);

    playerCountLabel = new QLabel("Players: 2");
    playerCountLabel->setStyleSheet("color: white;");

    startButton = new QPushButton("Start Game");

    layout->addWidget(title);
    layout->addWidget(playerSlider);
    layout->addWidget(playerCountLabel);
    layout->addWidget(startButton);
}

QSlider* HomePage::getSlider() const {
    return playerSlider;
}

QPushButton* HomePage::getStartButton() const {
    return startButton;
}

QLabel* HomePage::getPlayerCountLabel() const {
    return playerCountLabel;
}


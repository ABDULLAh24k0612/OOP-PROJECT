#include "homepage.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(50, 100, 50, 50);
    layout->setSpacing(30);

    // Logo image
    QLabel *logoLabel = new QLabel(this);
    QPixmap logoPixmap(":/assets/logo.png");  // Ensure this is in your .qrc
    logoLabel->setPixmap(logoPixmap.scaled(250, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);

    // Player count slider
    playerSlider = new QSlider(Qt::Horizontal);
    playerSlider->setRange(2, 4);
    playerSlider->setValue(2);

    playerCountLabel = new QLabel("Players: 2");
    playerCountLabel->setStyleSheet("color: white;");

    // Start button styled with image
    startButton = new QPushButton();
    startButton->setFixedSize(200, 80);
    startButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "background-image: url(:/assets/start_button.png);"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        );

    layout->addWidget(logoLabel);
    layout->addWidget(playerSlider);
    layout->addWidget(playerCountLabel);
    layout->addWidget(startButton, 0, Qt::AlignCenter);
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


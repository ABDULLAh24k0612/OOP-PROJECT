#include "gamepage.h"
#include "dice.h"
#include "board.h"

#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QRandomGenerator>
#include <QEvent>

GamePage::GamePage(QWidget *parent) : QWidget(parent), currentPlayerIndex(0), totalPlayers(2) {
    setupUI();
}

QPixmap GamePage::getRoundedPixmap(const QString &path, int size, int radius) {
    QPixmap src(path);
    src = src.scaled(size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap rounded(size, size);
    rounded.fill(Qt::transparent);

    QPainter painter(&rounded);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath pathClip;
    pathClip.addRoundedRect(0, 0, size, size, radius, radius);
    painter.setClipPath(pathClip);
    painter.drawPixmap(0, 0, src);
    return rounded;
}

void GamePage::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QGridLayout *grid = new QGridLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSpacing(0);

    QStringList iconPaths = {
        ":/assets/player1.png", ":/assets/player2.png",
        ":/assets/player3.png", ":/assets/player4.png"
    };

    for (const auto &path : iconPaths) {
        QLabel *icon = new QLabel();
        icon->setPixmap(QPixmap(path).scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        icon->setFixedSize(100, 100);
        icon->setStyleSheet("border: 4px solid transparent;");
        playerIcons.append(icon);
    }

    grid->addWidget(playerIcons[0], 0, 0, Qt::AlignTop | Qt::AlignLeft);
    grid->addWidget(playerIcons[1], 0, 2, Qt::AlignTop | Qt::AlignRight);
    grid->addWidget(playerIcons[2], 2, 0, Qt::AlignBottom | Qt::AlignLeft);
    grid->addWidget(playerIcons[3], 2, 2, Qt::AlignBottom | Qt::AlignRight);

    boardLabel = new QLabel();
    boardLabel->setPixmap(getRoundedPixmap(":/assets/board.png", 700, 50));
    boardLabel->setFixedSize(700, 700);
    boardLabel->setStyleSheet("border: 10px solid #804113; border-radius: 25%;");
    boardLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addWidget(boardLabel, 0, Qt::AlignCenter);

    diceLabel = new ClickableLabel(this);
    diceLabel->setPixmap(QPixmap(":/assets/1.png").scaled(70, 70));
    diceLabel->setFixedSize(70, 70);
    diceLabel->setScaledContents(true);
    diceLabel->setAlignment(Qt::AlignCenter);
    diceLabel->setCursor(Qt::PointingHandCursor);
    diceLabel->raise();
    diceLabel->show();

    connect(diceLabel, &ClickableLabel::clicked, this, &GamePage::rollDice);

    QStringList tokenPaths = {
        ":/assets/red.png", ":/assets/blue.png",
        ":/assets/green.png", ":/assets/purple.png"
    };

    for (const auto &path : tokenPaths) {
        QLabel *token = new QLabel(boardLabel);
        token->setPixmap(QPixmap(path).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        token->resize(60, 60);
        token->setScaledContents(true);
        token->setAttribute(Qt::WA_TranslucentBackground);
        token->hide();
        playerTokens.append(token);
    }

    grid->addLayout(centerLayout, 1, 1, Qt::AlignCenter);
    layout->addLayout(grid);

    installEventFilter(this);
}

void GamePage::startGame(int count) {
    totalPlayers = count;
    players = QVector<Player>(totalPlayers);
    currentPlayerIndex = 0;

    QPoint center = getBoardCoordinates(1);

    for (int i = 0; i < totalPlayers; ++i) {
        int tokenW = playerTokens[i]->width();
        int tokenH = playerTokens[i]->height();
        int x = center.x() - tokenW / 2 + (i % 2) * 12;
        int y = center.y() - tokenH / 2 + (i / 2) * 12;
        playerTokens[i]->move(x, y);
        playerTokens[i]->show();
    }

    for (int i = totalPlayers; i < playerTokens.size(); ++i) {
        playerTokens[i]->hide();
    }

    updateDiceImage(1);
    updatePlayerTurnIndicator();
}

void GamePage::rollDice() {
    int dice = Dice::roll();
    updateDiceImage(dice);
    movePlayer(currentPlayerIndex, dice);

    if (players[currentPlayerIndex].getPosition() >= 100) {
        diceLabel->setEnabled(false);
        diceLabel->setToolTip(QString("Player %1 wins!").arg(currentPlayerIndex + 1));
    }

    currentPlayerIndex = (currentPlayerIndex + 1) % totalPlayers;
    updatePlayerTurnIndicator();
}

void GamePage::updateDiceImage(int value) {
    diceLabel->setPixmap(QPixmap(Dice::getImagePath(value)).scaled(70, 70));
}

void GamePage::movePlayer(int index, int steps) {
    players[index].move(steps);
    int newPos = players[index].getPosition();
    newPos = Board::applySnakesAndLadders(newPos);
    players[index].setPosition(newPos);
    updatePlayerToken(index);
}

void GamePage::updatePlayerToken(int index) {
    QPoint pt = getBoardCoordinates(players[index].getPosition());
    int tokenSize = playerTokens[index]->width();
    pt.rx() -= tokenSize / 2;
    pt.ry() -= tokenSize / 2;

    int offset = 5;
    pt.rx() += (index % 2) * offset;
    pt.ry() += (index / 2) * offset;

    playerTokens[index]->move(pt);
}

void GamePage::updatePlayerTurnIndicator() {
    for (int i = 0; i < playerIcons.size(); ++i) {
        if (i == currentPlayerIndex) {
            playerIcons[i]->setStyleSheet("border: 3px solid yellow; border-radius: 10px;");
        } else {
            playerIcons[i]->setStyleSheet("border: 2px solid transparent;");
        }
    }
}

QPoint GamePage::getBoardCoordinates(int position) {
    return Board::getBoardCoordinates(position, boardLabel->width());
}

bool GamePage::eventFilter(QObject *watched, QEvent *event) {
    if (watched == this && event->type() == QEvent::Resize) {
        if (diceLabel && boardLabel) {
            int x = (width() - diceLabel->width()) / 2;
            int y = boardLabel->y() + boardLabel->height() + 10;
            diceLabel->move(x, y);
        }
    }
    return QWidget::eventFilter(watched, event);
}

#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class HomePage : public QWidget {
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);

    QSlider *getSlider() const;
    QPushButton *getStartButton() const;
    QLabel *getPlayerCountLabel() const;

private:
    QSlider *playerSlider;
    QPushButton *startButton;
    QLabel *playerCountLabel;
};

#endif // HOMEPAGE_H

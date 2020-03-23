#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "cell.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    enum State
    {
        xWinner, oWinner, draw, unfinished
    };

    explicit Window(QWidget *parent = nullptr);
    State getState() const;

public slots:
    void startGame();
    void updateGame();

private:
    QGridLayout *mainLayout;
    QLabel *label;
    Cell *c[3][3];
    QPushButton* startButton;
};

#endif // WINDOW_H

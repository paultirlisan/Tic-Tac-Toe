#include "window.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>

Cell::Shape Cell::expectedShape = Cell::Shape::xForm;

Window::Window(QWidget *parent) : QWidget {parent},
                                  mainLayout {new QGridLayout(this)},
                                  label {new QLabel()},
                                  startButton {new QPushButton()}
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            c[i][j] = new Cell;
            mainLayout->addWidget(c[i][j], i, j, Qt::AlignCenter);
            connect(c[i][j], SIGNAL(shapeChanged()), this, SLOT(updateGame()));
            c[i][j]->setBlocked(true);
        }

    mainLayout->addWidget(label, 3, 0, 1, 3);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("QLabel { color: Red;"
                                  "padding: 5px;"
                                  "font-size: 35px;"
                                  "font-family: Arial;"
                                  "border: 1px solid black;"
                                  "background-color: white; }");
    label->setText("Apasă start pentru a juca!");

    startButton->setText(tr("&Start"));
    startButton->setFont(QFont("Helvetica", 20));
    mainLayout->addWidget(startButton, 4, 0, 1, 3);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));

    QDesktopWidget *desktop = QApplication::desktop();
    int w = minimumWidth(), h = minimumHeight();
    setGeometry((desktop->width() - width()) / 2, (desktop->height() - height()) / 2, w, h);
    setFixedSize(w, h);
}

Window::State Window::getState() const
{
    int numberOfMoves = 0;

    // Check the state on rows
    for (int i = 0; i < 3; i++)
        if (c[i][0]->getShape() == c[i][1]->getShape() &&
            c[i][1]->getShape() == c[i][2]->getShape() &&
            c[i][0]->getShape() != Cell::nothing)
        {
            if (c[i][0]->getShape() == Cell::xForm)
                return xWinner;
            else
                return oWinner;
        }

    // Check the state on columns
    for (int j = 0; j < 3; j++)
        if (c[0][j]->getShape() == c[1][j]->getShape() &&
            c[1][j]->getShape() == c[2][j]->getShape() &&
            c[0][j]->getShape() != Cell::nothing)
        {
            if (c[0][j]->getShape() == Cell::xForm)
                return xWinner;
            else
                return oWinner;
        }

    // Check the state on the main diagonal
    if (c[0][0]->getShape() == c[1][1]->getShape() &&
        c[1][1]->getShape() == c[2][2]->getShape() &&
        c[0][0]->getShape() != Cell::nothing)
    {
        if (c[0][0]->getShape() == Cell::xForm)
            return xWinner;
        else
            return oWinner;
    }

    // Check the state on the secondary diagonal
    if (c[0][2]->getShape() == c[1][1]->getShape() &&
        c[1][1]->getShape() == c[2][0]->getShape() &&
        c[0][2]->getShape() != Cell::nothing)
    {
        if (c[0][2]->getShape() == Cell::xForm)
            return xWinner;
        else
            return oWinner;
    }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if ( !c[i][j]->isEmpty() )
                numberOfMoves++;
    if (numberOfMoves == 9)
        return draw;
    return unfinished;
}

void Window::startGame()
{
    label->setText(tr("Jocul a început"));
    Cell::setExpectedShape(Cell::xForm);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            c[i][j]->setBlocked(false);
            c[i][j]->setShape(Cell::nothing);
        }
}

void Window::updateGame()
{
    State currentState = getState();
    if (currentState == unfinished)
        return;

    if (currentState == xWinner)
        label->setText("X a câștigat!");
    else
        if (currentState == oWinner)
            label->setText("O a câștigat!");
        else
            label->setText("Remiză!");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            c[i][j]->setBlocked(true);
}

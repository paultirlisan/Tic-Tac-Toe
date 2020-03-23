#include "cell.h"
#include <QApplication>
#include <QBrush>

Cell::Cell(QWidget *parent) : QWidget(parent)
{
    isBlocked = false;
    realShape = nothing;
    width = height = 150;
    setFixedSize(QSize(width, height));
    setBackgroundRole(QPalette::Base);
}

void Cell::setShape(Cell::Shape s)
{
    if (!isBlocked)
    {
        realShape = s;
        update();
        if (realShape != nothing)
            emit shapeChanged();
    }
}

void Cell::setBlocked(bool blocked)
{
    isBlocked = blocked;
}

Cell::Shape Cell::getShape() const
{
    return realShape;
}

bool Cell::isEmpty()
{
    return realShape == nothing;
}

void Cell::setExpectedShape(Cell::Shape s)
{
    expectedShape = s;
}

void Cell::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QBrush background(Qt::GlobalColor::white);
    painter.fillRect(QRectF(0, 0, width, height), background);

    switch(realShape)
    {
        case xForm:
            painter.setPen(QPen(Qt::red, 12));
            painter.drawLine(width / 10, width / 10, 9 * width / 10, 9 * height / 10);
            painter.drawLine(9 * width / 10, width / 10, width / 10, 9 * height / 10);
            break;
        case oForm:
            painter.setPen(QPen(Qt::blue, 12));
            painter.drawEllipse(QRectF(width / 10, width / 10, 8 * width / 10, 8 * height / 10));
            break;
        default: break;
    }

    painter.save();
    painter.restore();
}

void Cell::mousePressEvent(QMouseEvent *)
{
    if (!isEmpty())
        return;
    setShape(Cell::expectedShape);
    if (Cell::expectedShape == xForm)
        Cell::expectedShape = oForm;
    else
        Cell::expectedShape = xForm;
}

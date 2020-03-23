#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include <QPainter>

class Cell : public QWidget
{
    Q_OBJECT
public:
    enum Shape
    {
        xForm, oForm, nothing
    };

    explicit Cell(QWidget *parent = nullptr);
    void setShape(Shape s);
    void setBlocked(bool blocked);
    Shape getShape() const;
    bool isEmpty();
    static void setExpectedShape(Shape s);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent*) override;

signals:
    void shapeChanged();

private:
    int width, height;
    Shape realShape;
    bool isBlocked;
    static Shape expectedShape;
};

#endif // CELL_H

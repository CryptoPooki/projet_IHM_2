#include "volume_widget.h"
#include "stdlib.h"
#include "iostream"
#include <QPixmap>
#include <QPainter>
#include <QtGui>


volume_widget::volume_widget()
{
    image.load(":/pics/vu_h.png");
    Nb_DEL = 34;
    Nb_DEL_on= 17;
    isSelected = false;
}

volume_widget::~volume_widget()
{
}

void volume_widget::mousePressEvent(QMouseEvent *)
{
   isSelected = true;
}

void volume_widget::mouseReleaseEvent(QMouseEvent *)
{
   isSelected = false;
}

void volume_widget::wheelEvent(QWheelEvent *event)
{
    if (isSelected && event->delta() > 0 && Nb_DEL_on < Nb_DEL - 1 && Nb_DEL_on >= 0) //Wheel up
    {
        Nb_DEL_on++;
        repaint();
    } else if (isSelected && event->delta() < 0 && Nb_DEL_on <= Nb_DEL && Nb_DEL_on > 0) //Wheel down
    {
        Nb_DEL_on--;
        repaint();
    }
}

void volume_widget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    painter->drawPixmap(0,0, image.width(), image.height() / Nb_DEL, image, 0, image.height() * Nb_DEL_on / Nb_DEL, image.width(), image.height() / Nb_DEL);
    delete painter;
}

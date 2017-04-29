#include "volume_widget.h"
#include "stdlib.h"
#include "iostream"
#include "math.h"
#include <QPixmap>
#include <QPainter>
#include <QtGui>


volume_widget::volume_widget()
{
    image.load(":/pics/vu_h.png");
    image = image.scaled(2*image.width(), 2*image.height());
    Nb_DEL = 34;
    Nb_DEL_on= 17;
    isSelected = false;
}

volume_widget::~volume_widget()
{
}

int volume_widget::get_volume()
{
    return (int) Nb_DEL_on*100/Nb_DEL;
}

void volume_widget::set_volume(int volume)
{
    Nb_DEL_on = (int) volume*Nb_DEL/100;
}

int volume_widget::get_Nb_DEL()
{
    return Nb_DEL;
}

int volume_widget::get_Nb_DEL_on()
{
    return Nb_DEL_on;
}

void volume_widget::set_Nb_DEL_on(int n)
{
    Nb_DEL_on = n;
}

void volume_widget::mouseMoveEvent(QMouseEvent *event)
{
    if (isSelected && event->y() <= 25+(image.width()/2) && event->y() >= 25-(image.width()/2))
    {
        if (event->x() < image.width() && (event->x() - 10) > 0)
        {
            Nb_DEL_on = (int) (event->x() - 10)/(image.width()/34);
            repaint();
            emit signal_volume();
        }
    }
}

void volume_widget::mousePressEvent(QMouseEvent *event)
{
   isSelected = true;
   if (event->y() <= 25+(image.width()/2) && event->y() >= 25-(image.width()/2))
   {
       if (event->x() < image.width() && (event->x() - 10) > 0)
       {
           int pos = event->x() - 10;
           int l = image.width() / 34;
           Nb_DEL_on = (int) pos / l;
           repaint();
           emit signal_volume();
       }
   }
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
        emit signal_volume();
    } else if (isSelected && event->delta() < 0 && Nb_DEL_on <= Nb_DEL && Nb_DEL_on > 0) //Wheel down
    {
        Nb_DEL_on--;
        repaint();
        emit signal_volume();
    }
}

void volume_widget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    painter->drawPixmap(10,25, image.width(), image.height() / Nb_DEL, image, 0, image.height() * Nb_DEL_on / Nb_DEL, image.width(), image.height() / Nb_DEL);
    delete painter;
}

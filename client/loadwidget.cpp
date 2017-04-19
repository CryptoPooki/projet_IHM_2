#include "loadwidget.h"
#include "iostream"
#include "stdlib.h"
#include <QPainter>
#include <QtGui>

Loadwidget::Loadwidget()
{
    image.load(":/pics/load.png");
    image = image.scaled(32,32);
}

Loadwidget::~Loadwidget()
{
}

void Loadwidget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);

    painter->drawPixmap(0,0,image);
    delete painter;
}

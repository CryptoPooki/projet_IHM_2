#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QThread>

class Loadwidget : public QWidget
{
    Q_OBJECT
private:
    QPixmap image; //Image chargée

public:
    //Constructeur
    explicit Loadwidget();
    //Destructeur
    ~Loadwidget();
    //Gestion des events ???

//Fonctions de QPainter pour afficher les QWidget
protected:
    void paintEvent(QPaintEvent *);
    QPainter* painter;
};

#endif // LOADWIDGET_H

#ifndef VOLUME_WIDGET_H
#define VOLUME_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QObject>
#include <stdlib.h>

class volume_widget : public QWidget
{
    Q_OBJECT
//Attibuts
    QPixmap image;                                          //Image chargée
    int Nb_DEL;                                             //Nombre de diodes
    int Nb_DEL_on;                                          //Nombre de diodes allumées
    bool isSelected;                                        //Flag indiquant si le Widget est sélectionné

//Méthodes
public:
    //Constructeur
    explicit volume_widget();
    //Destructeur
    ~volume_widget();
    //Comportement souris
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *event);
    //Les fonctions de redimensionnement sont héritées de la classe QWidget
    int get_volume();
    void set_volume(int volume);
    int get_Nb_DEL();
    int get_Nb_DEL_on();
    void set_Nb_DEL_on(int n);

signals:
    void signal_volume();

//Fonctions de QPainter pour afficher les Widget
protected:
    void paintEvent(QPaintEvent *);
    QPainter* painter;
};

#endif

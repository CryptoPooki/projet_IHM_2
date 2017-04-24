#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QtConcurrent/QtConcurrent>

class Serveur: public QObject
{
    Q_OBJECT
public:
    explicit Serveur(QObject *parent = 0);
    ~Serveur();
    bool pause = false;

public slots :
    void cible();

private:
    QLocalSocket *mpv=NULL;
    void sendRequestToMPV();
};

#endif // SERVEUR_H

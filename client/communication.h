#ifndef COMMUNICATION_H
#define COMMUNICATION_H


#include <QTcpSocket>
#include <QTcpServer>
#include "mainwindow.h"

class Communication: public QObject
{
    Q_OBJECT
public:
    Communication(MainWindow * W);
    bool writeData(QString dataString) ;
    int id ; // identifiant pour que le serveur puisse le virer de sa liste une fois la connexion terminée
    QTcpSocket * m_socket; // Sert pour envoyer des données au serveur
    QMainWindow * W;

private:

    bool connectToHost (QString host) ;
public slots:
    QString readyRead();
    void deconnexion();

};

#endif // COMMUNICATION_H

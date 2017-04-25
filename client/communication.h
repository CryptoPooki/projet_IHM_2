#ifndef COMMUNICATION_H
#define COMMUNICATION_H


#include <QTcpSocket>
#include <QTcpServer>

class Communication: public QObject
{
    Q_OBJECT
public:
    Communication();

private:
    QTcpServer * m_server; // Sert comme serveur pour la connexion du serveur
    QTcpSocket * m_server_com ; // Sert pour recevoir les données du serveur
    QTcpSocket * m_socket; // Sert pour envoyer des données au serveur

    bool writeData(QString dataString) ;
    bool connectToHost (QString host) ;
    void newConnection() ;
    void disconnected() ;
    QString readyRead() ;

};

#endif // COMMUNICATION_H

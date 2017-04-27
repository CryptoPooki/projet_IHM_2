#ifndef COMMUNICATION_H
#define COMMUNICATION_H


#include <QTcpSocket>
#include <QTcpServer>

class Communication: public QObject
{
    Q_OBJECT
public:
    Communication();
    bool writeData(QString dataString) ;

private:
    QTcpSocket * m_socket; // Sert pour envoyer des données au serveur

    bool connectToHost (QString host) ;
    QString readyRead() ;

};

#endif // COMMUNICATION_H

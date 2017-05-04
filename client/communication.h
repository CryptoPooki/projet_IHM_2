#ifndef COMMUNICATION_H
#define COMMUNICATION_H


#include <QTcpSocket>
#include <QTcpServer>
#include <QMainWindow>


namespace Ui {
  class MainWindow;
}

class Communication: public QObject
{
    Q_OBJECT
public:
    Communication();
    bool writeData(QString dataString) ;
    int id ; // identifiant pour que le serveur puisse le virer de sa liste une fois la connexion terminée
    QTcpSocket * m_socket; // Sert pour communiquer avec le serveur
    bool connected;

private:
    bool connectToHost (QString host) ;

public slots:
    QString readyRead();
    void deconnexion();

signals :
    void orderToWindow (QString);

};

#endif // COMMUNICATION_H

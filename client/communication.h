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
    bool writeData(QString dataString) ;    // Permet d'écrire les commandes dans le socket
    int id ;                                // identifiant pour que le serveur puisse le virer de sa liste une fois la connexion terminée
    QTcpSocket * m_socket;                  // Sert pour communiquer avec le serveur
    bool connected;                         // Flag indiquant si le client est connecté ou pas

private:
    bool connectToHost (QString host) ;     // Permet de se connecter

public slots:
    QString readyRead();                    // Récupère les retours du serveur
    void deconnexion();                     // Déconnexion

signals :
    void orderToWindow (QString);

};

#endif // COMMUNICATION_H

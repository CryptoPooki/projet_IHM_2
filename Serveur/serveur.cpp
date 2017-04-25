#include <QDebug>
#include <QTimer>
#include <QProcess>
#include <QTcpServer>
#include <QJsonObject>
#include <QJsonDocument>

#include "serveur.h"

Serveur::Serveur(QObject *parent) :
    QObject(parent),
    mpv(new QLocalSocket(this)),
    m_server(new QTcpServer(this))
{
    QProcess P;
    P.start("sh",QStringList()<< "-c" << " mpv --idle --input-ipc-server=/tmp/mpv-socket");
    P.waitForFinished(100);

    mpv->connectToServer( "/tmp/mpv-socket" ); //nom de la socket (p.ex./tmp/mpv-socket)

    if (mpv->waitForConnected())
        qDebug() << "connected to mpv";
    else {
        mpv->error();
        qDebug() << "connexion failed";
    }

    connect(m_server,SIGNAL(newConnection()), SLOT(newConnection()));

    m_server->listen(QHostAddress::Any,3000); // regarde sur toutes ses interfaces sur le port 3000



    QTimer * t = new QTimer();
    t->start(5000);
    connect(t, SIGNAL(timeout()), this , SLOT(cible()) );
    sendRequestToMPV();
}

void Serveur::newConnection()
{
    while(m_server->hasPendingConnections())
    {
        QTcpSocket * socket = m_server->nextPendingConnection();
        VClient.append(socket);
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
        qDebug() << "J'ai ajouté un client";
    }
}

void Serveur::disconnected()
{
}


void Serveur::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = new QByteArray();
    QJsonParseError error;
    QJsonDocument jDoc;
    QJsonObject jsonObject;

    while (socket->bytesAvailable() > 0)
    {
        buffer->append(socket->readAll());
        jDoc = QJsonDocument::fromJson(*buffer, &error);
        jsonObject = jDoc.object();
        qDebug() << "Le message envoyé est " + jsonObject.value("txt").toString();
    }
}

void Serveur::pause_f()
{
    QProcess P;
    if( !pause)
        P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\", \"pause\", true] }' | socat - /tmp/mpv-socket");
    else
        P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\", \"pause\", false] }' | socat - /tmp/mpv-socket");
    pause = !pause;
    P.waitForFinished();
    qDebug() << "chgt effectué";

}

void Serveur::chgtVolume(int value)
{
    QProcess P;
    P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"volume\"," << QString::number(value) << "] }' | socat - /tmp/mpv-socket");
    P.waitForFinished();
    qDebug() << "chgt effectué";
}

void Serveur::monterVolume()
{

}

void Serveur::baisseVolume()
{

}

void Serveur::chgtMusique()
{

}

void Serveur::avanceMusique()
{

}

void Serveur::reculeMusique()
{

}

void Serveur::chgtEndroitMusique()
{

}

void Serveur::cible()
{
    QProcess P;
    if( !pause)
        P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\", \"pause\", true] }' | socat - /tmp/mpv-socket");
    else
        P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\", \"pause\", false] }' | socat - /tmp/mpv-socket");
    pause = !pause;
    P.waitForFinished();
    qDebug() << "chgt effectué";
}

Serveur::~Serveur() {
    mpv->disconnectFromServer();
}

// envoye le message suivant à mpv:
//    { "command": ["loadfile", "nom du fichier"]}"
void Serveur::sendRequestToMPV(){
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append("loadfile");
    a.append( "/home/wilhelm/Goofy Goober Rock.mp3"  ); //donner le nom de fichier à lancer

    jsonObject["command"]=a;

    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (mpv!=NULL) {
      mpv->write(bytes.data(), bytes.length());
      mpv->flush();
    }
}

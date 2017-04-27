#include <QDebug>
#include <QTimer>
#include <QProcess>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>

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


    //QTimer * t = new QTimer();
    //t->start(5000);
    //connect(t, SIGNAL(timeout()), this , SLOT(cible()) );
    //sendRequestToMPV();
        chgtMusique("Smells Like Teen Spirit.mp3");
        //chgtEndroitMusique(100);
    //QThread::sleep(3);
    //mute();

}

void Serveur::newConnection()
{
    while(m_server->hasPendingConnections())
    {
        QTcpSocket * socket = m_server->nextPendingConnection();
        qDebug() << "J'ai ajouté un client";
        VClient.append(socket);
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
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
        if( jsonObject.value("txt").toString().compare("play"))
        {
            qDebug() << "Demande de play";
            play_f();
        }
        if( jsonObject.value("txt").toString().compare("pause"))
        {
            qDebug() << "Demande de pause";
            pause_f();
        }

        writeData("Resalut copain",socket);
        qDebug() << "j'ai dit resalut au copain =)";
    }
}


bool Serveur::writeData(QString dataString, QTcpSocket *socket)
{
    QJsonObject jsonObject;
    jsonObject["txt"] = dataString;
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);


    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(bytes); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

void Serveur::play_f()
{
    QProcess P;
    P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\", \"pause\", false] }' | socat - /tmp/mpv-socket");
    pause = false;
    P.waitForFinished();
    qDebug() << "play";
}

void Serveur::pause_f()
{
    QProcess P;
    P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\", \"pause\", true] }' | socat - /tmp/mpv-socket");
    pause = true;
    P.waitForFinished();
    qDebug() << "pause";
}

/*
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

} */

void Serveur::chgtVolume(int value)
{
    QProcess P;
    P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\",\"volume\"," + QString::number(value) + "] }' | socat - /tmp/mpv-socket");
    P.waitForFinished();
    qDebug() << "volume changé à " +  QString::number(value);
}

void Serveur::monterVolume()
{

}

void Serveur::baisseVolume()
{

}

void Serveur::mute()
{
    QProcess P;
    P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\",\"mute\",\"yes\"] }' | socat - /tmp/mpv-socket"); //active mute
    qDebug() <<" echo '{ \"command\": [\"set_property\",\"mute\",\"yes\"] }' | socat - /tmp/mpv-socket";
    P.waitForFinished();
    qDebug() << "mute activé";
    QThread::sleep(5);
    P.start("sh", QStringList() << "-c" <<"echo '{ \"command\": [\"set_property\",\"mute\",\"no\"] }' | socat - /tmp/mpv-socket"); // désactive mute
    P.waitForFinished();
    qDebug() << "mute désactivé";

}

void Serveur::chgtMusique(QString Name)
{
    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append("loadfile");
    a.append( "/home/wilhelm/"+ Name  ); //donner le nom de fichier à lancer
    jsonObject["command"]=a;

    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (mpv!=NULL) {
      mpv->write(bytes.data(), bytes.length());
      mpv->flush();
    }
}

void Serveur::avanceMusique()
{

}

void Serveur::reculeMusique()
{

}

void Serveur::chgtEndroitMusique(int time) // marche pas ça bug
{
    QProcess P;
    P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\",\"playback-time\"," + QString::number(time) +"] }' | socat - /tmp/mpv-socket"); //active mute
    P.waitForFinished();
    qDebug() << "mute activé";

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

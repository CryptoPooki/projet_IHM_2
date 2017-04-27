#include <QDebug>
#include <QTimer>
#include <QProcess>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QString>
#include <QPair>
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
    mute_flag = false;


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
        VClient.append(QPair<int,QTcpSocket*>(nextId,socket));
        qDebug() << VClient.size();
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        writeData(QString::fromStdString("identifiant ") + QString::number(nextId),socket);
        nextId ++;
    }
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
        QStringList L = jsonObject.value("txt").toString().split(" ");
        qDebug() << L[0].compare("play");
        if( L[0].compare("play") == 0 )
        {
            qDebug() << "Demande de play";
            play_f();
        }
        else if( L[0].compare("pause")== 0 )
        {
            qDebug() << "Demande de pause";
            pause_f();
        }

        else if( L[0].compare("mute")== 0 )
        {
            qDebug() << "Demande de mute";
            mute();
        }

        else if( L[0].compare("chgtMusique")== 0)
        {
            qDebug() << "Demande de Musique";
            chgtMusique(L[1]);
        }
        else if (L[0].compare("setVolume") == 0)
        {
            bool ok;
            qDebug() << "Demande de changer le volume";
            chgtVolume(L[1].toInt(&ok,10));
        }
        else if(L[0].compare("deconnexion") == 0)
        {
            bool ok;
            int id = L[1].toInt(&ok,10);
            qDebug() << QString::fromStdString("Suppression du client ") + QString::number(id);
            supprimeClient(id);
        }

        writeData("Resalut copain",socket);
        qDebug() << "j'ai dit resalut au copain =)";
    }
}

void Serveur::supprimeClient(int id)
{
    int i;
    for(i=0; i< VClient.size() ; i++)
    {
        if(  VClient.value(i).first ==id )
        {
            qDebug() << "trouvé =)";
            VClient.removeAt(i);
            return;
        }
    }
}

bool Serveur::writeData(QString dataString, QTcpSocket *socket)
{
    QJsonObject jsonObject;
    jsonObject["txt"] = dataString;
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);


    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        qDebug() << dataString + " a été écrit au client" ;
        socket->write(bytes); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
    {
        qDebug()<< "Not connected";
        return false;
    }
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
    qDebug() << QString::fromStdString("volume changé à ") +  QString::number(value);
}

void Serveur::mute()
{
    QProcess P;
    if(!mute_flag)
    {
        P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\",\"mute\",\"yes\"] }' | socat - /tmp/mpv-socket"); //active mute
        qDebug() << "mute activé";
        mute_flag = !mute_flag;
    }
    else
    {
        P.start("sh", QStringList() << "-c" <<"echo '{ \"command\": [\"set_property\",\"mute\",\"no\"] }' | socat - /tmp/mpv-socket"); // désactive mute
        qDebug() << "mute désactivé";
        mute_flag = !mute_flag;
    }
    P.waitForFinished();
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

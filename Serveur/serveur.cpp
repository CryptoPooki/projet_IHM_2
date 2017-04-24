#include <QDebug>
#include <QTimer>
#include <QProcess>

#include "serveur.h"

Serveur::Serveur(QObject *parent) :
    QObject(parent),
    mpv(new QLocalSocket(this))
{
    mpv->connectToServer( "/tmp/mpv-socket" ); //nom de la socket (p.ex./tmp/mpv-socket)

    if (mpv->waitForConnected())
        qDebug() << "connected to mpv";
    else {
        mpv->error();
        qDebug() << "arrive pas à se connecter";
    }

    QTimer * t = new QTimer();
    t->start(5000);
    connect(t, SIGNAL(timeout()), this , SLOT(cible()) );
    sendRequestToMPV();
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

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
#include <QStringList>

#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <QDirIterator>
#include "serveur.h"
#include "miseajourthread.h"
#include "musicfile.h"
#include "radiofile.h"
#include "automate_morceaux.h"
#include "automate_radio.h"

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
    play_flag = false;

    T =new MiseAJourThread();
    connect(T, SIGNAL(miseAJour()), this ,SLOT(MusiquePosition()) );

    automate_morceaux = new Automate_morceaux();
    automate_radio = new Automate_radio();
    musique = new musicfile();
    radio = new radiofile();

    //Initialisation des automates
    automate_morceaux->play->assignProperty(musique->path, "path", "/home/wilhelm/ProjetIHM2/projet_IHM_2/Musique/");
    automate_morceaux->play->assignProperty(musique->name, "name", "");
    automate_morceaux->play->assignProperty(musique->volume, "volume", 50);
    automate_morceaux->play->assignProperty(musique->pos, "pos", 0);
    automate_morceaux->play->assignProperty(musique->mute, "mute", false);

    automate_morceaux->pause->assignProperty(musique->path, "path", "/home/wilhelm/ProjetIHM2/projet_IHM_2/Musique/");
    automate_morceaux->pause->assignProperty(musique->name, "name", "");
    automate_morceaux->pause->assignProperty(musique->volume, "volume", 50);
    automate_morceaux->pause->assignProperty(musique->pos, "pos", 0);
    automate_morceaux->pause->assignProperty(musique->mute, "mute", false);

    automate_radio->play->assignProperty(musique->url, "url", "");
    automate_radio->play->assignProperty(musique->name, "name", "");
    automate_radio->play->assignProperty(musique->volume, "volume", 50);
    automate_radio->play->assignProperty(musique->mute, "mute", false);

    automate_radio->pause->assignProperty(musique->url, "url", "");
    automate_radio->pause->assignProperty(musique->name, "name", "");
    automate_radio->pause->assignProperty(musique->volume, "volume", 50);
    automate_radio->pause->assignProperty(musique->mute, "mute", false);

}

void Serveur::MusiquePosition()
{
    if (play_flag)
    {
        //Mise à jour de l'état play
        automate_morceaux->play->setProperty("position", getPlayedSeconds().toFloat()/(getPlayedSeconds().toFloat()+getRemainingSeconds().toFloat()) *100);

        //Mise à jour de l'historique
    } else
    {
        //Mise à jour de l'état pause
        automate_morceaux->pause->setProperty("position", getPlayedSeconds().toFloat()/(getPlayedSeconds().toFloat()+getRemainingSeconds().toFloat()) *100);

        //Mise à jour de l'historique
    }

    QString pos = QString::number( getPlayedSeconds().toFloat()/(getPlayedSeconds().toFloat()+getRemainingSeconds().toFloat()) *100) ;
    QString response = QString::fromStdString("move ")+ pos + QString::fromStdString(" ") + getPlayedSeconds()  +QString::fromStdString(" ") + getRemainingSeconds();
    writeEveryone(response );
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
        QThread::msleep(100);
        writeData( QString::fromStdString("initInfo ") + ListePLaylists().join("|"), socket);
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
            writeEveryone("play");
        }
        else if( L[0].compare("pause")== 0 )
        {
            qDebug() << "Demande de pause";
            pause_f();
            writeEveryone("pause");
        }

        else if( L[0].compare("mute")== 0 )
        {
            qDebug() << "Demande de mute";
            mute();
            writeEveryone("mute");
        }

        else if( L[0].compare("chgtMusique")== 0)
        {
            qDebug() << "Demande de Musique";
            chgtMusique(jsonObject.value("txt").toString().remove(0,12));
        }
        else if (L[0].compare("setVolume") == 0)
        {
            bool ok;
            qDebug() << "Demande de changer le volume";
            chgtVolume(L[1].toInt(&ok,10));
            writeEveryone( QString::fromStdString("setVolume ") + QString::number(L[1].toInt(&ok,10)));
        }
        else if(L[0].compare("deconnexion") == 0)
        {
            bool ok;
            int id = L[1].toInt(&ok,10);
            qDebug() << QString::fromStdString("Suppression du client ") + QString::number(id);
            supprimeClient(id);
        }
        else if (L[0].compare("getList") == 0)
        {
            qDebug() << "Demande de liste";
            QString tmp = L.at(1);
            QStringList List = ListePLaylistMusics(L.at(2));
            QString L = List.join("|");
            writeDataToClient(tmp.toInt(), QString::fromStdString("playList ") + L);
        }
        else if (L[0].compare("rewind") == 0)
        {
            qDebug() << "Recule";
            reculeMusique();
            writeEveryone("rewind");
        }
        else if (L[0].compare("forward") == 0)
        {
            qDebug() << "Avance";
            avanceMusique();
            writeEveryone("avance");
        }
        else if (L[0].compare("move") == 0)
        {
            qDebug() << QString::fromStdString("Pourcentage") + QString::number(L.at(1).toFloat());
            qDebug() << getRemainingSeconds();
            qDebug() << QString::number(L.at(1).toFloat() *  ( getPlayedSeconds().toFloat() + getRemainingSeconds().toFloat() ) /100);
            chgtEndroitMusique(L.at(1).toFloat() * (getPlayedSeconds().toFloat()+getRemainingSeconds().toFloat()) / 100);
            QString response = QString::fromStdString("move")+ L.at(1) + QString::fromStdString(" ") + getPlayedSeconds()  +QString::fromStdString(" ") + getRemainingSeconds();
            qDebug () << "La réponse  " + response;
            writeEveryone( response) ;
        }
        else if( L[0].compare("previous")==0)
        {
            previousMusic();
        }
        else if( L[0].compare("next") == 0)
        {
            nextMusic();
        }

    }
}

// ICI FAUT METTRE LE CHANGEMENT POUR ALLER A LA MUSIQUE D'AVANT
// CHANGER DE MUSIQUE -> chgtMusique
// CHANGER DE VOLUME -> chgtVolume

//J'y travaille
void Serveur::previousMusic()
{

}

void Serveur::nextMusic()
{

}


void Serveur::writeDataToClient(int id, QString Data)
{
    qDebug() << QString::fromStdString("Write to client") + QString::number(id);
    int i;
    for (i = 0; i < VClient.size() ; i++)
    {
        if( VClient.at(i).first == id)
        {
            writeData( Data, VClient.at(i).second );
            return;
        }
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

void Serveur::writeEveryone(QString response)
{
    int i;
    for(i=0;i<VClient.size(); i++)
        writeData( response,VClient.value(i).second);
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
    //Rentrer en état play
    automate_morceaux->setPlay(true);

    //Note : Vérifier la musique sélectionnée (délicat)

    QProcess P;
    P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\", \"pause\", false] }' | socat - /tmp/mpv-socket");
    pause = false;
    P.waitForFinished();
    qDebug() << "play";
    T->start();
}

void Serveur::pause_f()
{
    //Rentrer en état play
    automate_morceaux->setPlay(false);

    //Note : Vérifier la musique sélectionnée (délicat)
    QProcess P;
    P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\", \"pause\", true] }' | socat - /tmp/mpv-socket");
    pause = true;
    P.waitForFinished();
    qDebug() << "pause";
    T->quit();
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
    if (play_flag)
    {
        //Mise à jour de l'état play
        automate_morceaux->play->setProperty("volume", value);

        //Mise à jour de l'historique
    } else
    {
        //Mise à jour de l'état pause
        automate_morceaux->pause->setProperty("volume", value);

        //Mise à jour de l'historique
    }

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
        if (play_flag)
        {
            //Mise à jour de l'état play
            automate_morceaux->play->setProperty("mute", true);

            //Mise à jour de l'historique
        } else
        {
            //Mise à jour de l'état pause
            automate_morceaux->pause->setProperty("mute", true);

            //Mise à jour de l'historique
        }

        P.start("sh", QStringList() << "-c" <<" echo '{ \"command\": [\"set_property\",\"mute\",\"yes\"] }' | socat - /tmp/mpv-socket"); //active mute
        qDebug() << "mute activé";
        mute_flag = !mute_flag;
    }
    else
    {
        if (play_flag)
        {
            //Mise à jour de l'état play
            automate_morceaux->play->setProperty("mute", false);

            //Mise à jour de l'historique
        } else
        {
            //Mise à jour de l'état pause
            automate_morceaux->pause->setProperty("mute", false);

            //Mise à jour de l'historique
        }

        P.start("sh", QStringList() << "-c" <<"echo '{ \"command\": [\"set_property\",\"mute\",\"no\"] }' | socat - /tmp/mpv-socket"); // désactive mute
        qDebug() << "mute désactivé";
        mute_flag = !mute_flag;
    }
    P.waitForFinished();
}

void Serveur::chgtMusique(QString nom)
{
    //Mise à jour du nom
    automate_morceaux->play->setProperty("nom", nom);

    //Mise à jour de l'historique

    //Est-ce que ça play automatiquement quand on change de musique ?

    QJsonObject jsonObject ;
    QJsonArray a ;
    a.append("loadfile");
    a.append( "/home/wilhelm/ProjetIHM2/projet_IHM_2/Musique/"+ nom  ); //donner le nom de fichier à lancer
    jsonObject["command"]=a;
    qDebug() << jsonObject["command"];
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    if (mpv!=NULL) {
      mpv->write(bytes.data(), bytes.length());
      mpv->flush();
    }
    T->start();
    //TagLib::FileRef f(QFile::encodeName("/home/wilhelm/mus.mp3").constData());


}

QString Serveur::getPlayedSeconds()
{
    QProcess P;
    QString time = "";
    int i=0;
    P.start("sh", QStringList() << "-c" <<  QString::fromStdString("echo '{\"command\":[ \"get_property\",\"time-pos\"] }' | socat - /tmp/mpv-socket"));
    P.waitForFinished();
    QString sortie = P.readAllStandardOutput();
    while( !(sortie.at(i) >= '0' && sortie.at(i)<='9') )
    {
        i++;
    }
    while ( sortie.at(i) != '.')
    {
        time.append(sortie.at(i));
        i++;
    }
    time.append(sortie.at(i));
    i++;
    while (sortie.at(i) >= '0' && sortie.at(i) <='9')
    {
        time.append(sortie.at(i));
        i++;
    }
    return time;
}

QString Serveur::getRemainingSeconds()
{
    QProcess P;
    QString time = "";
    int i=0;
    P.start("sh", QStringList() << "-c" <<  QString::fromStdString("echo '{\"command\":[ \"get_property\",\"time-remaining\"] }' | socat - /tmp/mpv-socket"));
    P.waitForFinished();
    QString sortie = P.readAllStandardOutput();
    while( !(sortie.at(i) >= '0' && sortie.at(i)<='9') )
    {
        i++;
    }
    while ( sortie.at(i) != '.')
    {
        time.append(sortie.at(i));
        i++;
    }
    time.append(sortie.at(i));
    i++;
    while (sortie.at(i) >= '0' && sortie.at(i) <='9')
    {
        time.append(sortie.at(i));
        i++;
    }
    return time;
}

void Serveur::avanceMusique()
{
    QString time = getPlayedSeconds();
    chgtEndroitMusique( time.toFloat() + 5.0);
}

void Serveur::reculeMusique()
{
    QString time = getPlayedSeconds();
    chgtEndroitMusique( fmax(time.toFloat() - 5.0,0.0));
}

void Serveur::chgtEndroitMusique(float time)
{
    if (play_flag)
    {
        //Mise à jour de l'état play
        automate_morceaux->play->setProperty("position", time);

        //Mise à jour de l'historique
    } else
    {
        //Mise à jour de l'état pause
        automate_morceaux->pause->setProperty("position", time);

        //Mise à jour de l'historique
    }
    QProcess P;
    P.start("sh", QStringList() << "-c" <<  QString::fromStdString("echo '{\"command\":[ \"set_property\",\"time-pos\",")+ QString::number(time) +QString::fromStdString("] }' | socat - /tmp/mpv-socket"));
         //   " echo '{ \"command\": [\"set_property\",\"playback-time\"," + QString::number(time) +"] }' | socat - /tmp/mpv-socket"); //active mute
    P.waitForFinished();
    qDebug() <<QString::fromStdString( "echo \"{\"command\":[ \"set_property\",\"time-pos\",")+ QString::number(time) +QString::fromStdString("] }' | socat - /tmp/mpv-socket" );

}

QStringList Serveur::ListePLaylists ()
{
    QStringList L;
    QStringList tmp;
    QString nextList;
    QDirIterator *it = new QDirIterator("/home/wilhelm/ProjetIHM2/projet_IHM_2/Musique");
    while(it->hasNext())
    {
        nextList = it->next();
        tmp = nextList.split("/");
        nextList = tmp.at( tmp.size() -1 ) ;
        if ( nextList.compare(".") != 0 && nextList.compare("..") != 0)
        {
            qDebug() << nextList;
            L.append(nextList);
        }
    }
    return L;
}

QStringList Serveur::ListePLaylistMusics( QString Folder)
{
    qDebug() << Folder;
    QStringList L;
    QStringList tmp;
    QString nextList;
    QDirIterator *it = new QDirIterator(QString::fromStdString("/home/wilhelm/ProjetIHM2/projet_IHM_2/Musique/") + Folder);
    qDebug() << QString::fromStdString("Folder : ") + Folder;
    while(it->hasNext())
    {
        nextList = it->next();
        tmp = nextList.split("/");
        nextList = tmp.at( tmp.size() -1 ) ;
        if ( nextList.compare(".") != 0 && nextList.compare("..") != 0)
        {
            qDebug() << QString::fromStdString("    ") +nextList;
            L.append(nextList);
        }
    }
    return L;
}

Serveur::~Serveur() {
    mpv->disconnectFromServer();
}

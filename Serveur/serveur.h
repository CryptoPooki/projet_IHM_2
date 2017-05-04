#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
#include <QLocalServer>
#include <QTcpSocket>
#include <QLocalSocket>
#include <QtConcurrent/QtConcurrent>
#include <QVector>
#include <QTcpServer>
#include <QPair>
#include <QStringList>
#include <QMap>

#include "miseajourthread.h"
#include "musicfile.h"
#include "radiofile.h"
#include "automate_morceaux.h"
#include "automate_radio.h"

class Serveur: public QObject
{
    Q_OBJECT
public:
    explicit Serveur(QObject *parent = 0);
    ~Serveur();
    bool pause = false;
    int nextId = 0;

public slots :
    void newConnection();
    void readyRead();

    void play_f();
    void pause_f();

    void chgtVolume(int value);
    void mute();
    void chgtMusique(QString nom);
    void avanceMusique();
    void reculeMusique();
    void chgtEndroitMusique(float time);

    bool writeData(QString dataString, QTcpSocket* socket);
    void supprimeClient(int id);
    void writeEveryone(QString response);
    QStringList ListePLaylists();
    QStringList ListePLaylistMusics( QString Folder);
    void writeDataToClient(int id, QString Data);
    QString getPlayedSeconds();
    QString getRemainingSeconds();
    void MusiquePosition();
    void previousMusic();
    void nextMusic();
    QMap<QString, QString> getTags(QString fileName);



private:
    QLocalSocket *mpv=NULL;
    QVector<QPair<int ,QTcpSocket*>> VClient;
    QTcpServer * m_server;
    Automate_morceaux *automate_morceaux;
    Automate_radio *automate_radio;
    musicfile *musique;
    radiofile *radio;
    QString URL_radio[6] = {
        "http://www.skyrock.fm/stream.php/tunein16_128mp3.mp3",
        "http://cdn.nrjaudio.fm/audio1/fr/30001/mp3_128.mp3?origine=fluxradios",
        "http://direct.franceinfo.fr/live/franceinfo-lofi.mp3",
        "http://direct.franceinter.fr/live/franceinter-midfi.mp3",
        "http://direct.francemusique.fr/live/francemusique-midfi.mp3",
        "http://a.files.bbci.co.uk/media/live/manifesto/audio/simulcast/hls/uk/sbr_high/ak/bbc_6music.m3u8"
    };
    /*Note: pour écouter la radio avec mpv
        ->mpv 'url_de_la_radio'
    */
    bool m_running;
    bool mute_flag;
    QThread* T;


};

#endif // SERVEUR_H

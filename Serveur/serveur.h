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



private:
    QLocalSocket *mpv=NULL;
    QVector<QPair<int ,QTcpSocket*>> VClient;
    QTcpServer * m_server;
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
    (+2 points sur le projet)
    */
    bool m_running;
    bool mute_flag;


};

#endif // SERVEUR_H

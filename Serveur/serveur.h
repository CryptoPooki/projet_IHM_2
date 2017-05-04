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
    //Constructeur/Desctruteur
    explicit Serveur(QObject *parent = 0);
    ~Serveur();
    bool pause = false;                     //Flag indiquant si le serveur est en pause
    int nextId = 0;                         //Compteur de clients connectés et également ID donné au client connecté

public slots :
    void newConnection();                   //Slot de gestion des connexions
    void readyRead();                       //Slot de gestion des communication entre le serveur et tous les clients

    void play_f();                          //Slot de gestion de lecture de musique
    void pause_f();                         //Slot de gestion de pause

    void chgtVolume(int value);             //Slot de gestion du volume
    void mute();                            //Slot de gestion du mute
    void chgtMusique(QString nom);          //Slot de gestion de changement de musique
    void avanceMusique();                   //Slot de gestion du fast foward
    void reculeMusique();                   //Slot de gestion du rewind
    void chgtEndroitMusique(float time);    //Slot de gestion de changement de position de la tête de lecture

    bool writeData(QString dataString, QTcpSocket* socket); //Slot de gestion des informations envoyé au client avec les sockets
    void supprimeClient(int id);            //Slot de gestion du suppression de client
    void writeEveryone(QString response);   //Slot permettant la diffusion à tous les clients
    QStringList ListePLaylists();           //Slot de parcours des dossiers/listes
    QStringList ListePLaylistMusics( QString Folder); //Slot de parcours des morceaux
    void writeDataToClient(int id, QString Data); //Slot d'envoie d'informations à un client spécifique
    QString getPlayedSeconds();             //Slot retournant le temps lu sous forme de chaine de caractères
    QString getRemainingSeconds();          //Slot retournant le temps restant sour forme de chaine de caractères
    void MusiquePosition();                 //Slot mettant à jour la position dans l'automate
    void previousMusic();                   //Slot qui joue la musique précédente dans l'historique
    void nextMusic();                       //Slot qui joue la musique suivante dans l'historique
    QMap<QString, QString> getTags(QString fileName); //Récupération des données de tags avec Taglib



private:
    QLocalSocket *mpv=NULL;                 //Socket pour MPV
    QVector<QPair<int ,QTcpSocket*>> VClient;
    QTcpServer * m_server;                  //Interface/Serveur TCP pour les clients
    Automate_morceaux *automate_morceaux;   //Automate pour les morceaux
    Automate_radio *automate_radio;         //Automate pour la radio
    musicfile *musique;                     //Fichier musique pour l'automate morceaux
    radiofile *radio;                       //Fichier radio pour l'automate radio
    QString URL_radio[6] = {                //Liste d'URL de radios
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
    bool m_running;                         //Flag indiquant si le serveur tourne ou pas
    bool mute_flag;                         //Flag indiquant si le serveur est mute ou pas
    QThread* T;                             //Thread pour la mise à jour régulière du serveur



};

#endif // SERVEUR_H

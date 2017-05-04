#ifndef MUSICFILE_H
#define MUSICFILE_H

#include <QObject>

/* Afin de attribuer des propriétés à un état, il faut attribuer un Q_Object auquel
 * nous associons des propriétés, d'où le rôle de musicfile.
 */

class musicfile : public QObject
{
    Q_OBJECT

public:
    //Constructeur & Destructeur
    musicfile();
    ~musicfile();

    //Propriétés
    QString path;   //Chemin d'accès de la musique
    QString name;   //Nom de la musique
    bool play;      //Flag indiquant si le morceau est joué
    int volume;     //Volume
    float pos;      //Position (absolue) de lecture
    bool mute;      //Flag indiquant si le morceau est muté

    //Get & Set
    QString get_path();
    QString get_name();
    bool get_play();
    int get_volume();
    float get_pos();
    bool get_mute();

    void set_path(QString p);
    void set_name(QString n);
    void set_play(bool p);
    void set_volume(int v);
    void set_pos(float p);
    void set_mute(bool m);
};

#endif // MUSICFILE_H

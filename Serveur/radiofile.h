#ifndef RADIOFILE_H
#define RADIOFILE_H

#include <QObject>

class radiofile : public QObject
{
    Q_OBJECT
public:
    radiofile();
    ~radiofile();

    QString url;
    QString name;
    bool play;
    int volume;
    bool mute;

    //Get & Set
    QString get_url();
    QString get_name();
    bool get_play();
    int get_volume();
    bool get_mute();

    void set_url(QString u);
    void set_name(QString n);
    void set_play(bool p);
    void set_volume(int v);
    void set_mute(bool m);
};

#endif // RADIOFILE_H

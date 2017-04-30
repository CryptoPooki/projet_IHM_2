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
    int volume;
    bool mute;

    //Get & Set
    QString get_url();
    QString get_name();
    int get_volume();
    bool get_mute();

    void set_url(QString u);
    void set_name(QString n);
    void set_volume(int v);
    void set_mute(bool m);
};

#endif // RADIOFILE_H

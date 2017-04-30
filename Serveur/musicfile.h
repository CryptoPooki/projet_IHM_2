#ifndef MUSICFILE_H
#define MUSICFILE_H

#include <QObject>

class musicfile : public QObject
{
    Q_OBJECT

public:
    musicfile();
    ~musicfile();

    QString path;
    QString name;
    int volume;
    float pos;
    bool mute;

    //Get & Set
    QString get_path();
    QString get_name();
    int get_volume();
    float get_pos();
    bool get_mute();

    void set_path(QString p);
    void set_name(QString n);
    void set_volume(int v);
    void set_pos(float p);
    void set_mute(bool m);
};

#endif // MUSICFILE_H

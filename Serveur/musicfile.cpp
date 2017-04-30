#include "musicfile.h"

musicfile::musicfile()
{
}

musicfile::~musicfile()
{
}

//Get & Set
QString musicfile::get_path()
{
    return path;
}

QString musicfile::get_name()
{
    return name;
}

bool musicfile::get_play()
{
    return play;
}

int musicfile::get_volume()
{
    return volume;
}

float musicfile::get_pos()
{
    return pos;
}

bool musicfile::get_mute()
{
    return mute;
}

void musicfile::set_path(QString p)
{
    path = p;
}

void musicfile::set_name(QString n)
{
    name = n;
}

void musicfile::set_play(bool p)
{
    play = p;
}

void musicfile::set_volume(int v)
{
    volume = v;
}

void musicfile::set_pos(float p)
{
    pos = p;
}

void musicfile::set_mute(bool m)
{
    mute = m;
}

#include "radiofile.h"

radiofile::radiofile()
{
}

radiofile::~radiofile()
{
}

//Get & Set
QString radiofile::get_url()
{
    return url;
}

QString radiofile::get_name()
{
    return name;
}

int radiofile::get_volume()
{
    return volume;
}

bool radiofile::get_mute()
{
    return mute;
}

void radiofile::set_url(QString u)
{
    url = u;
}

void radiofile::set_name(QString n)
{
    name = n;
}

void radiofile::set_volume(int v)
{
    volume = v;
}

void radiofile::set_mute(bool m)
{
    mute = m;
}

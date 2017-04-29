#include <QThread>

#include "miseajourthread.h"

MiseAJourThread::MiseAJourThread()
{
}

void MiseAJourThread::run()
{
    while(true)
    {
        QThread::sleep(1);
        emit miseAJour( );
    }
}

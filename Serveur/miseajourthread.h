#ifndef MISEAJOURTHREAD_H
#define MISEAJOURTHREAD_H

#include <QThread>

class MiseAJourThread: public QThread
{
    Q_OBJECT
public:
    MiseAJourThread();
    void run();

signals:
    void miseAJour(void);
};

#endif // MISEAJOURTHREAD_H


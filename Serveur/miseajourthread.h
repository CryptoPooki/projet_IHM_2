#ifndef MISEAJOURTHREAD_H
#define MISEAJOURTHREAD_H

#include <QThread>

class MiseAJourThread: public QThread
{
    Q_OBJECT
public:
    MiseAJourThread();      //Fonction permettant une MAJ régulière de l'état du serveur
    void run();             //Surcharge de run() pour lancer le thread

signals:
    void miseAJour(void);   //Signal de MAJ
};

#endif // MISEAJOURTHREAD_H


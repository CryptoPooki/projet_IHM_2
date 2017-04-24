#include <QCoreApplication>

#include "serveur.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Serveur s;
    return a.exec();

/*    QApplication a(argc, argv);
    MainWindow w;
    w.show();*/
}

#include "mainwindow.h"
#include "clienttest.h"
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QJsonObject jsonObject;
    jsonObject["txt"] = "salut";
    ClientTest* C = new ClientTest();
    C->connectToHost("localhost");
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)+"\n";
    bool reussite =C->writeData(bytes);
    if (reussite)
        qDebug() << "J'ai Réussi";
    else
        qDebug() << "J'ai Fail";

    return a.exec();
}

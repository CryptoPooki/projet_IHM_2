#ifndef CLIENTTEST_H
#define CLIENTTEST_H

#include <QObject>
#include <QTcpSocket>

class ClientTest : public QObject
{
    Q_OBJECT
public:
    ClientTest();
    bool connectToHost (QString host);
    bool writeData(QByteArray data);
    QByteArray IntToArray(qint32 source);

    QTcpSocket *m_socket;
};

#endif // CLIENTTEST_H

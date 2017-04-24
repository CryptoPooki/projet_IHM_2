#include "clienttest.h"

#include <QTcpSocket>
#include <QDataStream>


ClientTest::ClientTest():
    m_socket(new QTcpSocket(this))
{
}

bool ClientTest::connectToHost (QString host)
{
    m_socket->connectToHost(host,3000);
    return m_socket->waitForConnected();
}


bool ClientTest::writeData(QByteArray data)
{
    if(m_socket->state() == QAbstractSocket::ConnectedState)
    {
        m_socket->write(data); //write the data itself
        return m_socket->waitForBytesWritten();
    }
    else
        return false;
}



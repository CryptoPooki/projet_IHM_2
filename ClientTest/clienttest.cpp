#include "clienttest.h"

#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>



ClientTest::ClientTest():
    m_socket(new QTcpSocket(this))
{
}

bool ClientTest::connectToHost (QString host)
{
    m_socket->connectToHost(host,3000);
    connect(m_socket, SIGNAL(readyRead()), SLOT(readyRead()));
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


void ClientTest::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = new QByteArray();
    QJsonParseError error;
    QJsonDocument jDoc;
    QJsonObject jsonObject;

    while (socket->bytesAvailable() > 0)
    {
        buffer->append(socket->readAll());
        jDoc = QJsonDocument::fromJson(*buffer, &error);
        jsonObject = jDoc.object();
        qDebug() << "Le message envoyé est " + jsonObject.value("txt").toString();
    }
}

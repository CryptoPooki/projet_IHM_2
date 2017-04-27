#include "communication.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>


Communication::Communication():
    m_socket(new QTcpSocket(this))
{
    if(!connectToHost("localhost"))
        qDebug() << "Fail connexion to serveur";
}

bool Communication::connectToHost (QString host)
{
    m_socket->connectToHost(host,3000);
    return m_socket->waitForConnected();
}


bool Communication::writeData(QString dataString)
{
    QJsonObject jsonObject;
    jsonObject["txt"] = dataString;
    if( ! connectToHost("localhost") )
            qDebug() << "Connexion échouée";
    QByteArray bytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);


    if(m_socket->state() == QAbstractSocket::ConnectedState)
    {
        m_socket->write(bytes); //write the data itself
        return m_socket->waitForBytesWritten();
    }
    else
        return false;
}




QString Communication::readyRead()
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
    return jsonObject.value("txt").toString();
}

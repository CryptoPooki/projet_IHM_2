#include "communication.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>


Communication::Communication():
    m_socket(new QTcpSocket(this)),
    m_server(new QTcpServer(this))
{
    connect(m_server,SIGNAL(newConnection()), SLOT(newConnection())); // lorsque le serveur se connecte
    m_server->listen(QHostAddress::Any,3001); // faudra changer ça quand il y aura plusieurs clients qui se connectes / Enfin quoique on peut laisser

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



void Communication::newConnection()
{
    while(m_server->hasPendingConnections())
    {
        m_server_com = m_server->nextPendingConnection();
        connect(m_server_com, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(m_server_com, SIGNAL(disconnected()), SLOT(disconnected()));
        qDebug() << "J'ai ajouté un client";
    }
}

void Communication::disconnected()
{
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

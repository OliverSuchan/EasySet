#include "server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    m_packetHandler = new PacketHandler();
    if(this->listen(QHostAddress::Any, 1337))
    {
        qDebug() << "Server wurde gestartet!";
        connect(this, SIGNAL(newConnection()), this, SLOT(newCon()));
    }
    else
        std::cerr << this->errorString().toStdString() << std::endl;
}

void Server::on_readyRead()
{
    QTcpSocket *senderSocket = dynamic_cast<QTcpSocket*>(sender());
    if(senderSocket)
    {
        qDebug() << senderSocket->localAddress().toString() << ": " << senderSocket->readAll();
    }
}

void Server::deleteLater()
{
    QTcpSocket *senderSocket = dynamic_cast<QTcpSocket*>(sender());
    for(Clients::iterator it = m_clients.begin(); it != m_clients.end(); ++it)
    {
        if(*it == senderSocket)
            m_clients.erase(it);
    }
    Server::deleteLater();
}

void Server::newCon()
{
    qDebug() << "Neue Verbindung verfügbar.";

    QTcpSocket *newSocket = this->nextPendingConnection();
    if(newSocket)
    {
        m_clients.push_back(newSocket);
        connect(newSocket ,SIGNAL(readyRead()),this,SLOT(on_readyRead()));
        connect(newSocket ,SIGNAL(disconnected()),newSocket ,SLOT(deleteLater()));
        sendFSPacket(newSocket);
    }
}

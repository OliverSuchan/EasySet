#include "server.hpp"

Server::Server(QObject *parent, int p_port) :
    QTcpServer(parent)
{
    m_packetHandler = new PacketHandler;
    if(listen(QHostAddress::Any, p_port))
    {
        connect(this, SIGNAL(newConnection()), this, SLOT(newCon()));
        connect(m_packetHandler, SIGNAL(readClick(QTcpSocket*,QByteArray)), this, SLOT(retrieveClick(QTcpSocket*,QByteArray)));
        connect(m_packetHandler, SIGNAL(readTurnPacket(QTcpSocket*)), this, SLOT(retrievePlayerTurn(QTcpSocket*)));
    }
    else
    {
        std::cerr << "Fehler beim Starten des Servers!" << std::endl;
        std::cerr << errorString().toStdString() << std::endl;
    }
}

void Server::deleteLater()
{
    QTcpServer::deleteLater();
}

void Server::newCon()
{
    QTcpSocket *newSocket = static_cast<QTcpSocket*>(nextPendingConnection());
    if(newSocket)
    {
        connect(newSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(newSocket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
        m_clients.push_back(std::make_tuple(newSocket, 0, std::list<Card *>()));
    }
    //sendWaitTimePacket();
    sendFSPacket();
    sendScoreboard();
}

void Server::onReadyRead()
{
    QTcpSocket *senderSocket = static_cast<QTcpSocket*>(sender());
    if(senderSocket)
    {
        m_packetHandler->processPackets(senderSocket->readAll(), senderSocket);
    }
}

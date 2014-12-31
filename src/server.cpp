#include "src/server.hpp"

Server::Server(QObject *parent, int p_port) :
    QTcpServer(parent)
{
    m_packetHandler = std::unique_ptr<PacketHandler>(new PacketHandler);
    if(listen(QHostAddress::Any, p_port))
    {
        std::cout << "Server wurde gestartet" << std::endl;
        connect(this, SIGNAL(newConnection()), this, SLOT(newCon()));
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
        m_clients.push_back(std::make_tuple(newSocket, 0, std::list<std::unique_ptr<Card>>()));
    }
    sendFSPacket(nullptr);
}

void Server::onReadyRead()
{
    QTcpSocket *senderSocket =static_cast<QTcpSocket*>(sender());
    if(senderSocket)
    {
        m_packetHandler->processPackets(senderSocket->readAll(), std::unique_ptr<QTcpSocket>(senderSocket));
    }
}

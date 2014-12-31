#include "client.hpp"

Client::Client(QObject *p_parent, QHostAddress p_ip, int p_port) :
    QTcpSocket(p_parent)
{
    m_packetHandler = std::move(std::unique_ptr<PacketHandler>(new PacketHandler));
    connectToHost(p_ip, p_port);
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_packetHandler.get(), SIGNAL(readScore(short)), this, SLOT(retrieveScore(short)));
    connect(m_packetHandler.get(), SIGNAL(readField(QByteArray)), Window::getInstance(), SLOT(retrieveField(QByteArray)));
}

void Client::retrieveBestScore(short p_score)
{

}

void Client::retrieveScore(short p_score)
{

}

void Client::onReadyRead()
{
    std::cout << "client; incoming message" << std::endl;
    QTcpSocket *serverSocket = static_cast<QTcpSocket*>(sender());
    if(serverSocket)
    {
        m_packetHandler->processPackets(serverSocket->readAll(), std::unique_ptr<QTcpSocket>(serverSocket));
    }
}

#include "client.hpp"

Client::Client(QObject *p_parent, QHostAddress p_ip, int p_port) :
    QTcpSocket(p_parent)
{
    m_packetHandler = new PacketHandler;
    connectToHost(p_ip, p_port);
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_packetHandler, SIGNAL(readScore(short)), this, SLOT(retrieveScore(short)));
    connect(m_packetHandler, SIGNAL(readField(QByteArray)), Window::getInstance(), SLOT(retrieveField(QByteArray)));
    //connect(m_packetHandler, SIGNAL(readWaitTime(unsigned int)), Window::getInstance(), SLOT(retrieveWaitTime(unsigned int)));
    connect(m_packetHandler, SIGNAL(readDeckLength(short)), Window::getInstance(), SLOT(retrieveDeckLength(short)));
    connect(m_packetHandler, SIGNAL(readScores(QByteArray)), Window::getInstance(), SLOT(retrieveScores(QByteArray)));
    connect(m_packetHandler, SIGNAL(readGameStartedPacket()), Window::getInstance(), SLOT(retrieveGameStarted()));
    connect(m_packetHandler, SIGNAL(readGameFinishedPacket()), Window::getInstance(), SLOT(retrieveGameFinished()));
}

void Client::onReadyRead()
{
    QTcpSocket *serverSocket = static_cast<QTcpSocket*>(sender());
    if(serverSocket)
    {
        m_packetHandler->processPackets(serverSocket->readAll(), serverSocket);
    }
}

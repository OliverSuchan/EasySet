#include "client.h"

Client::Client(QObject *p_parent, QHostAddress p_ip, int p_port) :
    QTcpSocket(p_parent)
{
    m_packetHandler = new PacketHandler();
    connectToHost(p_ip, p_port);
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_packetHandler, SIGNAL(readScore(short)), this, SLOT(retrieveScore(short)));
    connect(m_packetHandler, SIGNAL(readField(QByteArray)), this, SLOT(retrieveField(QByteArray)));
}

void Client::onReadyRead()
{
    QTcpSocket* senderSocket = dynamic_cast<QTcpSocket*>(sender());
    if(senderSocket)
    {
        std::cout << senderSocket->readAll().toHex().toStdString().c_str() << std::endl;
        m_packetHandler->processPackets(senderSocket->readAll());
    }
}

void Client::retrieveScore(short p_score)
{
    std::cout << p_score << std::endl;
}

void Client::retrieveField(QByteArray p_field)
{
    std::cout << p_field.toHex().toStdString().c_str() << std::endl;
}

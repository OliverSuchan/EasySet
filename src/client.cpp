#include "../include/client.h"

Client::Client(QHostAddress ip, QObject *parent) :
    QTcpSocket(parent)
{
    m_packetAdministration = new PacketAdministration();
    connectToHost(ip, 1337);
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_packetAdministration, SIGNAL(readScore(short)), this, SLOT(retrieveScore(short)));
}

void Client::onReadyRead()
{
    QTcpSocket* senderSocket = dynamic_cast<QTcpSocket*>(sender());
    if(senderSocket)
    {
        m_packetAdministration->processPackets(senderSocket->readAll());

        QByteArray message = "Kuchen";
        senderSocket->write(message);
    }
}

void Client::retrieveScore(short p_score)
{
    std::cout << p_score << std::endl;
}

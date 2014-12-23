#include "client.h"

Client::Client(QObject *p_parent, QHostAddress p_ip, int p_port) :
    QTcpSocket(p_parent)
{
    m_packetAdministration = new PacketAdministration();
    connectToHost(p_ip, p_port);
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(m_packetAdministration, SIGNAL(readScore(short)), this, SLOT(retrieveScore(short)));
    connect(m_packetAdministration, SIGNAL(readField(void*)), this, SLOT(retrieveScore(short)));
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

void Client::retrieveField(void *p_field)
{
    std::cout << static_cast<const char*>(p_field) << std::endl;
}

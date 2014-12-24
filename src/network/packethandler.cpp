#include "packethandler.h"
#include "card.h"

PacketHandler::PacketHandler(QObject *p_parent) :
    QObject(p_parent)
{
}

void PacketHandler::processPackets(QByteArray p_packets)
{
    while(p_packets.size())
    {
        QByteArray packet = QByteArray(p_packets[1], Qt::Uninitialized);
        std::move(p_packets.begin(), p_packets.begin() + static_cast<int>(p_packets[1]), packet.begin());
        p_packets.remove(0, p_packets[1]);
        processPacket(packet);
    }
}

QByteArray PacketHandler::makeFSPacket(void *p_field)
{
    QByteArray packet;
    packet.append(FIELD_SYNCHRO);
    Card *currentCard = static_cast<Card*>(p_field);
    do
    {
        packet.append(char(*currentCard));
        currentCard = *currentCard + 1;
    }
    while(currentCard != p_field && currentCard != nullptr);
    packet.insert(1, packet.size() + 1);
    return packet;
}

QByteArray PacketHandler::makeClickPacket(void* p_card)
{
    QByteArray packet;
    packet.append(CLICK);
    packet.append(static_cast<Card*>(p_card)->attributesToByte());
    packet.insert(1, packet.size() + 1);
    return packet;
}

QByteArray PacketHandler::makeScorePacket(short p_score)
{
    QByteArray packet;
    packet.append(SCORE);
    packet.append(p_score);
    packet.insert(1, packet.size() + 1);
    return packet;
}

void PacketHandler::processPacket(QByteArray p_packet)
{
    if(p_packet.size())
    {
        QByteArray packet;
        std::copy(p_packet.begin() + 2, p_packet.end(), packet.begin());
        switch(p_packet[0])
        {
        case SCORE:
            emit readScore(p_packet[2]);
            break;

        case FIELD_SYNCHRO:
            emit readField(packet);
            break;

        case CLICK:
            break;

        default:
            std::cerr << "Dieser Pakettyp existiert nicht." << std::endl;
        }
    }
}

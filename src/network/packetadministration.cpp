#include "packetadministration.h"

PacketAdministration::PacketAdministration(QObject *p_parent) :
    QObject(p_parent)
{
}

void PacketAdministration::processPackets(QByteArray p_packets)
{
    while(p_packets.size())
    {
        QByteArray packet = QByteArray(p_packets[1], Qt::Uninitialized);
        std::move(p_packets.begin(), p_packets.begin() + static_cast<int>(p_packets[1]), packet.begin());
        p_packets.remove(0, p_packets[1]);
        processPacket(packet);
    }
}

QByteArray PacketAdministration::makeFSPacket(void *p_field)
{
    QByteArray packet;
    packet.append(FIELD_SYNCHRO);
    packet.append(static_cast<const char*>(p_field));
    packet.insert(1, packet.size() + 1);
    return packet;
}

QByteArray PacketAdministration::makeClickPacket(void* p_card)
{
    QByteArray packet;
    packet.append(CLICK);
    packet.append(static_cast<const char*>(p_card));
    packet.insert(1, packet.size() + 1);
    return packet;
}

QByteArray PacketAdministration::makeScorePacket(short p_score)
{
    QByteArray packet;
    packet.append(SCORE);
    packet.append(p_score);
    packet.insert(1, packet.size() + 1);
    return packet;
}

void PacketAdministration::processPacket(QByteArray p_packet)
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
            emit readField(static_cast<void*>(packet.data()));
            break;

        case CLICK:
            break;

        default:
            std::cerr << "Dieser Pakettyp existiert nicht." << std::endl;
        }
    }
}

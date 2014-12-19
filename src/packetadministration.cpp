#include "../include/packetadministration.h"

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

void PacketAdministration::processPacket(QByteArray p_packet)
{
    if(p_packet.size())
    {
        switch(p_packet[0])
        {
        case SCORE:
            emit readScore(p_packet[2]);
            break;

        case FIELD_SYNCHRO:
            break;

        case CLICK:
            break;

        default:
            std::cerr << "Dieser Pakettyp existiert nicht." << std::endl;
        }
    }
}

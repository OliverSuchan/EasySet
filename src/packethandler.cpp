#include "packethandler.hpp"

PacketHandler::PacketHandler(QObject *parent) :
    QObject(parent)
{
}

void PacketHandler::processPackets(QByteArray p_packets, std::unique_ptr<QTcpSocket> p_socket)
{
    while(p_packets.size())
    {
        QByteArray packet = QByteArray(p_packets[1], Qt::Uninitialized);
        std::move(p_packets.begin(), p_packets.begin() + static_cast<int>(p_packets[1]), packet.begin());
        p_packets.remove(0, p_packets[1]);
        processPacket(packet, std::move(p_socket));
    }
}

QByteArray PacketHandler::makeFSPacket(std::list<std::unique_ptr<Card> > &p_field)
{
    QByteArray packet;
    packet.append(FIELD_SYNCHRO);
    for(auto it = p_field.begin(); it != p_field.end(); ++it)
    {
        packet.append(char(**it));
    }
    packet.insert(1, packet.size() + 1);
    return packet;
}

QByteArray PacketHandler::makeClickPacket(std::list<std::unique_ptr<Card> > &p_cards)
{
    QByteArray packet;
    packet.append(CLICK);
    for(auto it = p_cards.begin(); it != p_cards.end(); ++it)
    {
        packet.append(char(**it));
    }
    packet.insert(1, packet.size() + 1);
    return packet;
}

void PacketHandler::processPacket(QByteArray p_packet, std::unique_ptr<QTcpSocket> p_socket)
{
    if(p_packet.size())
    {
        QByteArray packet(p_packet[1] - 2, Qt::Uninitialized);;
        std::copy(p_packet.begin() + 2, p_packet.end(), packet.begin());
        switch(p_packet[0])
        {
        case FIELD_SYNCHRO:
            emit readField(packet);
            break;

        case CLICK:
            emit readClick(p_socket.get(), p_packet[2]);
            break;

        case SCORE:
            emit readScore(p_packet[2]);
            break;

        default:
            std::cerr << "Dieser Pakettyp existiert nicht!" << std::endl;
        }
    }
}

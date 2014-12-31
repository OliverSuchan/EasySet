#include "controller.hpp"

Card* Controller::searchForCard(short p_color, short p_shape, short p_number, short p_opacity, Server::Cards &p_cards)
{
    for(auto it = p_cards.begin(); it != p_cards.end(); ++it)
    {

        if((*it)->m_color == p_color && (*it)->m_shape == p_shape && (*it)->m_number == p_number && (*it)->m_opacity == p_opacity)
            return (*it).get();
    }
    return nullptr;
}

void Controller::sendFSPacket(QTcpSocket *p_socket)
{
    QByteArray packet = m_packetHandler->makeFSPacket(m_field);
    std::cout << packet.toHex().toStdString() << std::endl;
    if(p_socket)
    {
        p_socket->write(packet);
        p_socket->flush();
    }
    else
    {
        for(auto it = m_clients.begin(); it != m_clients.end(); ++it)
        {
            std::get<0>(*it)->write(packet);
            std::get<0>(*it)->flush();
        }
    }
}

bool Controller::check(Server::Cards &p_cards)
{
    if(p_cards.size() == 3)
    {
        Card sum(0, 0, 0, 0);
        for(auto it = p_cards.begin(); it != p_cards.end(); ++it)
        {
            sum = sum + **it;
        }
        if(!(sum.m_color + sum.m_number + sum.m_opacity + sum.m_shape))
            return true;
    }
    return false;
}

Controller::Controller(QObject *p_parent) :
    Server(p_parent),
    m_deck(),
    m_field()
{
    srand(time(NULL));
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                for(int l = 0; l < 3; l++)
                {
                    m_deck.push_back(std::unique_ptr<Card>(new Card(i, j, k, l)));
                }
            }
        }
    }
    draw(12);
}

void Controller::draw(short p_count)
{
    if(m_deck.size() < p_count)
        p_count = m_deck.size();
    for(int i = 0; i < p_count; i++)
    {
        int index = rand() % this->m_deck.size();
        auto it = m_deck.begin();
        std::advance(it, index);
        m_field.push_back(std::move(*it));
        m_deck.remove(*it);
    }
    sendFSPacket(nullptr);
}

void Controller::retrieveClick(QTcpSocket *p_client, char p_card)
{
    std::cout << "click" << std::endl;
    /*for(auto it = m_clients.begin(); it != m_clients.end(); ++it)
    {
        if(std::get<0>(*it).get() == p_client)
        {
            if(std::get<2>(*it).size() < 3)
            {
                Card *curCard = searchForCard((p_card >> 6) & 0x03, (p_card >> 4) & 0x03, (p_card >> 2) & 0x03, p_card & 0x03, std::get<2>(*it));
                std::get<2>(*it).push_back(std::unique_ptr<Card>(curCard));
            }

            if(std::get<2>(*it).size() == 3)
            {
                std::cout << "check: " << check(std::get<2>(*it)) << std::endl;
            }
            return;
        }
    }
    for(auto it = m_clients.begin(); it != m_clients.end(); ++it)
    {
        std::cout << std::get<2>(*it).size() << std::endl;
    }*/
}

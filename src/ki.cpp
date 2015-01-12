#include "ki.hpp"

void KI::selectField()
{
    while(true)
    {
        if(m_gameEnded.load())
            return;
        std::this_thread::sleep_for(std::chrono::seconds(20));
        if(m_gameEnded.load())
            return;

        m_curMutex.lock();



        std::list<Card*> checkList;

        if(m_inputLocked.load())
            goto exit;
        // teste alle möglichen Kombinationen
        for(auto first = m_field.begin(); first != m_field.end(); ++first)
        {
            for(auto second = m_field.begin(); second != m_field.end(); ++second)
            {
                for(auto third = m_field.begin(); third != m_field.end(); ++third)
                {
                    checkList.clear();
                    // falls die Karten nicht gleich sind
                    if(*first != *second && *first != *third && *second != *third)
                    {
                        checkList.push_back(*first);
                        checkList.push_back(*second);
                        checkList.push_back(*third);
                        if(Controller::check(checkList))
                        {
                            if(m_inputLocked.load())
                                goto exit;
                            sendTurnPacket();
                            std::string packet{ char(**first), char(**second), char(**third) };
                            sendClickPacket(packet.c_str());
                            goto exit;
                        }
                    }
                }
            }
        }
        exit:
        m_curMutex.unlock();
    }
}

KI::KI(QObject *p_parent, QHostAddress p_ip, int p_port) :
    Player(p_parent, p_ip, p_port)
{
    m_gameEnded.store(false);
    m_inputLocked.store(false);
    connect(m_packetHandler, &PacketHandler::readField, this, &KI::retrieveField);
    connect(m_packetHandler, &PacketHandler::readGameStartedPacket, this, &KI::retrieveGameStarted);
    connect(m_packetHandler, &PacketHandler::readGameFinishedPacket, this, &KI::retrieveGameEnded);
    connect(m_packetHandler, &PacketHandler::readLockedPacket, this, &KI::retrieveInputLocked);
    connect(m_packetHandler, &PacketHandler::readUnlockedPacket, this, &KI::retrieveInputUnlocked);
}

KI::~KI()
{
    m_gameEnded.store(true);
    m_curThread.join();
}

void KI::retrieveInputUnlocked()
{
    m_inputLocked.store(false);
}

void KI::retrieveInputLocked()
{
    m_inputLocked.store(true);
}

void KI::retrieveGameStarted()
{
    m_curThread = std::thread(&KI::selectField, this);
}

void KI::retrieveGameEnded()
{
    m_gameEnded.store(true);
    m_curThread.join();
}

void KI::retrieveField(QByteArray p_field)
{
    for(auto it = m_field.begin(); it != m_field.end(); ++it)
    {
        Card *curCard = static_cast<Card*>(*it);
        delete curCard;
        curCard = nullptr;
    }
    m_field.clear();
    for(auto it = p_field.begin(); it != p_field.end(); ++it)
    {
        Card *card = new Card((*it >> 6) & 0x03, (*it >> 4) & 0x03, (*it >> 2) & 0x03, *it & 0x03);
        m_field.push_back(card);
    }
}


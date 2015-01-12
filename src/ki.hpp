#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
#include "player.hpp"
#include "card.hpp"

class KI : public Player
{
private:
    std::atomic<bool> m_gameEnded;
    std::atomic<bool> m_inputLocked;
    std::list<Card*> m_field;
    std::thread m_curThread;
    std::mutex m_curMutex;
    void selectField();

public:
    KI(QObject *p_parent = 0, QHostAddress p_ip = QHostAddress::LocalHost, int p_port = 1337);
    ~KI();

public slots:
    void retrieveInputUnlocked();
    void retrieveInputLocked();
    void retrieveGameStarted();
    void retrieveGameEnded();
    void retrieveField(QByteArray p_field);
};

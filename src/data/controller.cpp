#include "Controller.h"

bool Controller::check(Card & a, Card & b, Card & c){
    Card sum = a + b + c;
    if(!(sum.m_color + sum.m_number + sum.m_opacity + sum.m_shape))
        return true;
    return false;
}


Card *Controller::getField()
{
    return m_field;
}


Controller::Controller(QObject *p_parent) :
    Server(p_parent)
{
    long t;
    time(&t);
    srand((unsigned)t);

    int l = 1;
    this->m_deckCard = new Card(0, 0, 0, 0);
    Card* first = this->m_deckCard;

   // std::vector<Card> cards;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                while(l < 3)
                {
                    this->m_deckCard->m_nextCard = new Card(i, j, k, l);
                    this->m_deckCard->m_nextCard->m_previousCard = this->m_deckCard;
                    this->m_deckCard = this->m_deckCard->m_nextCard;
                    //cards.push_back(Card(i, j, k, l));
                    l++;
                }
                l=0;
            }
        }
    }
    first->m_previousCard = this->m_deckCard;
    this->m_deckCard->m_nextCard = first;
    draw();
}

void Controller::insertDeckCard(Card &a)
{
    a.m_nextCard = this->m_deckCard->m_nextCard;
    a.m_previousCard = this->m_deckCard;
    *(this->m_deckCard->m_nextCard->m_previousCard) = a;
    *(this->m_deckCard->m_nextCard) = a;
}
void Controller::draw()
{
//    this->m_deckCard = this->m_deckCard + (rand() % decklength);
//    this->m_deckCard->m_previousCard->m_nextCard = this->m_deckCard->m_nextCard;
//    this->m_deckCard->m_nextCard->m_previousCard = this->m_deckCard->m_previousCard;
//    this->m_deckCard->m_nextCard = this->m_deckCard->m_previousCard = nullptr;
//    if(m_field == nullptr)
//        this->m_field = this->m_deckCard
    std::cout << "Anzahl der Karten im Deck: " << m_deckCard->size() << std::endl;
    m_field = m_deckCard;

}

void Controller::sendFSPacket(QTcpSocket *p_client)
{
    p_client->write(m_packetHandler->makeFSPacket(this->m_field));
    p_client->flush();
}

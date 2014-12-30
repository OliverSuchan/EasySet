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
    Card *drawnCard = *this->m_deckCard + (rand() % this->m_deckCard->size());
    drawnCard->m_previousCard->m_nextCard = drawnCard->m_nextCard;
    drawnCard->m_nextCard->m_previousCard = drawnCard->m_previousCard;
    this->m_deckCard = drawnCard->m_nextCard;
    if(m_field)
    {
        drawnCard->m_nextCard = m_field;
        drawnCard->m_previousCard = m_field->m_previousCard;
        m_field->m_previousCard->m_nextCard = drawnCard;
        m_field->m_previousCard = drawnCard;
    }
    else
    {
        m_field = drawnCard;
        m_field->m_nextCard = m_field;
        m_field->m_previousCard = m_field;
    }
    std::cout << "Anzahl der Karten im Deck: " << m_deckCard->size() << std::endl;
    std::cout << "Anzahl der Karten auf dem Spielfeld: " << m_field->size() << std::endl;
}

void Controller::sendFSPacket(QTcpSocket *p_client)
{
    p_client->write(m_packetHandler->makeFSPacket(this->m_field));
    p_client->flush();
}

bool Controller::checkField()   // Untersucht alle Kombinationen des Feldes auf ein Set
{
    Card* a, b, c;
    a = m_field;
    b = a->m_nextCard;
    c = b->m_nextCard;
    for(int i = 0; i < m_field->size(); i++)
    {
        for(int j = i + 1; j < m_field->size(); j++)
        {
            for(int k = j + 1; k < m_field->size(); k++)
            {
                if(check(a,b,c)) return true;
                c = c->m_nextCard;
            }
            b = b->m_nextCard;
            c = b->m_nextCard;
        }
        a = a->m_nextCard;
        b = a->m_nextCard;
        c = b->m_nextCard;
    }
}

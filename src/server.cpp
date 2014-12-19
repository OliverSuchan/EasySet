#include "../include/server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    if(this->listen(QHostAddress::Any, 1337))
    {
        qDebug() << "Server wurde gestartet!";
        connect(this, SIGNAL(newConnection()), this, SLOT(newCon()));
    }
    else
        std::cerr << this->errorString().toStdString() << std::endl;
}

void Server::on_readyRead()
{
    QTcpSocket * senderSocket = dynamic_cast<QTcpSocket*>(sender());
    if(senderSocket)
    {
        qDebug() << senderSocket->localAddress().toString() << ": " << senderSocket->readAll();
    }
}

void Server::newCon()
{
    qDebug() << "Neue Verbindung verfügbar.";

    QTcpSocket * newSocket = this->nextPendingConnection();
    if(newSocket)
    {
        std::string message{0x3, 0x3, 0x1};
        newSocket->write(message.c_str());
        newSocket->flush();
        connect(newSocket ,SIGNAL(readyRead()),this,SLOT(on_readyRead()));
        connect(newSocket ,SIGNAL(disconnected()),newSocket ,SLOT(deleteLater()));
    }
}

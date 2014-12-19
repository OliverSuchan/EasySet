#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);

signals:

public slots:
    void newCon();
    void on_readyRead();

};

#endif // SERVER_H

#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor);

signals:
    void newDescripter(qintptr socketDescriptor);

public slots:
};

#endif // MYTCPSERVER_H

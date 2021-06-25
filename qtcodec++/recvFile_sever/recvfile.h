#ifndef RECVFILE_H
#define RECVFILE_H

#include <QThread>
#include <QTcpSocket>


class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(qintptr socket ,QObject *parent = nullptr);
protected:
    void run();
private:
    QTcpSocket *m_socket;

signals:
    void over();

public slots:
};

#endif // RECVFILE_H

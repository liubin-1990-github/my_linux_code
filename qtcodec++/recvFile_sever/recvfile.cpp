#include "recvfile.h"
#include <QFile>

RecvFile::RecvFile(qintptr socket  ,QObject *parent) : QThread(parent)
{
    m_socket=new QTcpSocket(this);
    m_socket->setSocketDescriptor(socket);

}

void RecvFile::run()
{
    QFile *file=new QFile("recv.txt");
    file->open(QFile::WriteOnly);

    //recv data
    connect(m_socket,&QTcpSocket::readyRead,this,[=]()
    {
        static int count = 0;
        static int total = 0;
        if(count == 0)
        {
            m_socket->read((char*)&total,4);
        }
        QByteArray all= m_socket->readAll();
        count+=all.size();

        file->write(all);
        if(count==total)
        {
            m_socket->close();
            m_socket->deleteLater();
            file->close();
            file->deleteLater();
            emit over();
        }
    });
    exec();
}

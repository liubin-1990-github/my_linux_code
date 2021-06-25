#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include "recvfile.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_tcp=new MyTcpServer(this);
    connect(m_tcp,&MyTcpServer::newDescripter,this,[=](qintptr sock){
//        QTcpSocket *socket=m_tcp->nextPendingConnection();
        //creat thread
        RecvFile *subthread=new RecvFile(sock);
        subthread->start();
        connect(subthread,&RecvFile::over,this,[=]()
        {
            subthread->exit();
            subthread->wait();
            subthread->deleteLater();
            QMessageBox::information(this,"recv file","over");
        });

    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startListen_clicked()
{
    int port = ui->lineEdit_port->text().toInt();
    m_tcp->listen(QHostAddress::Any,port);

}

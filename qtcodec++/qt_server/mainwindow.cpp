#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //
    m_tcp = new QTcpServer(this);
    ui->port_2->setText("8899");

    //listen
    connect(ui->start,&QPushButton::clicked,[=]()
    {
       int port = ui->port_2->text().toInt();
       m_tcp->listen(QHostAddress::Any,port);
       ui->start->setEnabled(true);
    });
    connect(m_tcp,&QTcpServer::newConnection,this,[=]()
    {
        socket = m_tcp->nextPendingConnection();
        connect(socket,&QTcpSocket::readyRead,this,[=]()
        {
            QByteArray data = socket->readAll();
            ui->textEdit_history->append("client say"+data);
        });
        connect(socket,&QTcpSocket::disconnected,[=]()
        {
            socket->close();
            socket->deleteLater();
             ui->textEdit_history->append("client  disconnected");
        });
    });

    connect(ui->send,&QPushButton::clicked,[=]()
    {
        QString msg = ui->textEdit_message->toPlainText();
        socket->write(msg.toUtf8());
        ui->textEdit_history->append("sever say"+msg);
    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

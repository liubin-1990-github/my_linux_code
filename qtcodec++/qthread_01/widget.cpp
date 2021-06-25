#include "widget.h"
#include "ui_widget.h"
#include "mythread.h"
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    MyThread *subThread = new MyThread;
    MyThread_Bubble *bubbleThread = new MyThread_Bubble;
    MyThread_Quick *quickThread = new MyThread_Quick;
    connect(this,&Widget::starting,subThread,&MyThread::recvNum);

    connect(ui->pushButton,&QPushButton::clicked,[=](){
       emit starting(10000);
       subThread->start();
    });
    connect(subThread,&MyThread::sendArray,bubbleThread,&MyThread_Bubble::recvNum);
    connect(subThread,&MyThread::sendArray,quickThread,&MyThread_Quick::recvNum);
    connect(subThread,&MyThread::sendArray,this,[=](QVector<int> list){
        bubbleThread->start();
        quickThread->start();

        for(auto v :list)
        {
            ui->randList->addItem(QString::number(v));
        }
    });



    connect(bubbleThread,&MyThread_Bubble::sendArray,this,[=](QVector<int> list){

        for(auto v :list)
        {
            ui->bubbleList->addItem(QString::number(v));
        }
    });

    //
    connect(quickThread,&MyThread_Quick::sendArray,this,[=](QVector<int> list){

        for(auto v :list)
        {
            ui->quickList->addItem(QString::number(v));
        }
    });
    connect(this,&Widget::destroyed,this,[=](){
       subThread->quit();
       subThread->wait();
       delete subThread;
    });
    //



}

Widget::~Widget()
{
    delete ui;
}

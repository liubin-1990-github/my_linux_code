#include "qtcpclient.h"
#include "ui_qtcpclient.h"

QTCPclient::QTCPclient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTCPclient)
{
    ui->setupUi(this);
}

QTCPclient::~QTCPclient()
{
    delete ui;
}

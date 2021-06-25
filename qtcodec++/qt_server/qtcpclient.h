#ifndef QTCPCLIENT_H
#define QTCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class QTCPclient;
}

class QTCPclient : public QWidget
{
    Q_OBJECT

public:
    explicit QTCPclient(QWidget *parent = 0);
    ~QTCPclient();

private:
    Ui::QTCPclient *ui;
};

#endif // QTCPCLIENT_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include "mytcpserver.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    void on_startListen_clicked();

private:
    Ui::Widget *ui;
    MyTcpServer *m_tcp;
};

#endif // WIDGET_H

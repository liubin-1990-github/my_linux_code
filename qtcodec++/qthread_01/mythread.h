#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
protected:
    void run();

private:
    int m_num;

signals:
    void sendArray(QVector<int> num);

public slots:
    void recvNum(int num);
};



class MyThread_Bubble : public QThread
{
    Q_OBJECT
public:
    explicit MyThread_Bubble(QObject *parent = nullptr);
protected:
    void run();

private:
    QVector<int> m_list;

signals:
    void sendArray(QVector<int> num);

public slots:
    void recvNum(QVector<int> list);
};


class MyThread_Quick : public QThread
{
    Q_OBJECT
public:
    explicit MyThread_Quick(QObject *parent = nullptr);
protected:
    void run();
private:
    void quickSort(QVector<int> &s,int l , int r);

private:
    QVector<int> m_list;

signals:
    void sendArray(QVector<int> num);

public slots:
    void recvNum(QVector<int> list);
};

#endif // MYTHREAD_H

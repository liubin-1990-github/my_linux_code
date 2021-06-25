#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>
#include <algorithm>

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run()
{
    QVector<int> list;
    QElapsedTimer time;
    time.start();
   for(int i= 0 ;i<m_num;i++)
   {
       list.push_back(qrand()%10000);
   }
   int t= time.elapsed();
   qDebug()<<"creat 10000 random number use"<<t<<"ms";
   emit sendArray(list);
}

void MyThread::recvNum(int num)
{
    m_num=num;
}

MyThread_Bubble::MyThread_Bubble(QObject *parent) :QThread(parent)
{

}

void MyThread_Bubble::run()
{
    qDebug()<<"bubblesort thread addr  "<<QThread::currentThread();
    QElapsedTimer time;
    time.start();


    int temp;
    for(int i=0;i<m_list.size();++i)
    {
        for(int j =0;j<m_list.size()-i-1;++j)
        {
            if(m_list[j]>m_list[j+1])
            {
                temp=m_list[j];
                m_list[j]=m_list[j+1];
                m_list[j+1]=temp;
            }
        }
    }
    int t= time.elapsed();
    qDebug()<<"bubble sort use"<<t<<"ms";
    emit sendArray(m_list);
}

void MyThread_Bubble::recvNum(QVector<int> list)
{
    m_list=list;
}

MyThread_Quick::MyThread_Quick(QObject *parent) :QThread(parent)
{

}

void MyThread_Quick::run()
{
    qDebug()<<"quicksort thread addr  "<<QThread::currentThread();
    QElapsedTimer time;
    time.start();


    std::sort(m_list.begin(),m_list.end());
    int t= time.elapsed();
    qDebug()<<"quick sort use"<<t<<"ms";
    emit sendArray(m_list);
}

void MyThread_Quick::quickSort(QVector<int> &s, int l, int r)
{
    if(l<r)
    {
        int i=l;
        int j=r;
        //the first save in x
        int x=s[i];
        while(i<j)
        {
            while(i<j&&s[j]>=x)
            {
                //move left untile s[j]<=x
                j--;
            }
            if(i<j)
            {
                s[i++]=s[j];
                //s[i] switch to j then ++
            }
            while(i<j&&s[i]<x)
            {
                i++;
            }
            if(i<j)
            {
                s[j--]=s[i];
            }


        }
        s[i]=x;
        quickSort(s,1,i-1);
        quickSort(s,i+1,r);
    }
}

void MyThread_Quick::recvNum(QVector<int> list)
{
    m_list=list;
}

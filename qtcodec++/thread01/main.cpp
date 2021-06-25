#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <sys/stat.h>





using namespace std;
class Counter{
public:
    int getcount() const{return m_count;}
    void addcount() {m_count++;}
    Counter():m_count(0){}
private:
    int m_count;
};
int work(int a)
{
    return a+a;
}
template<class iter>
void dowork(Counter &c,int &value,iter begin,iter end)
{
    for(;begin!=end;++begin)
    {
        c.addcount();
        value+=work(*begin);
    }
}
void printAll(int a,int b,int c)
{
    cout<<a<<"   "<<b<<"    "<<c<<endl;
}
void initThread()
{
    int q=1;
    int w=2;
    int e=3;
    thread t([=](){
        printAll(q,w,e);
    });
    t.join();
}
bool ifFinish(Counter c,int n)
{
    if(c.getcount()==n)
        return true;
}


int main()
{


    cout << "Hello World!" << endl;
    vector<int>v;
    Counter count;
    int value = 0 ;
    for(int i=0;i<10000000;++i)
    {
        v.push_back(rand()%100);
    }
    for(auto info:v)
    {
       count.addcount();
       value+=work(info);
    }
    Counter count2;
    int value1=0;
    thread printcount([&count2](){
        while (ifFinish(count2,10000000)) {

        }
    });
    auto iter1 = v.begin()+v.size()/3;
    auto iter2 = iter1+v.size()/3;
    auto iterEnd = v.end();
    auto iterStart = v.begin();
//    thread c([iterStart,iter1,&count2,&value1](){
//        for(auto iter = iterStart;iter!=iter1;++iter)
//        {
//            count2.addcount();
//            value1 +=work(*iter);
//        }
//    });
//    thread d([iter1,iter2,&count2,&value1](){
//        for(auto iter = iter1;iter!=iter2;++iter)
//        {
//            count2.addcount();
//            value1+=work(*iter);
//        }
//    });

    thread c([&count2,&value1,iterStart,iter1](){
        dowork(count2,value1,iterStart,iter1);
    });

    thread d([&count2,&value1,iter1,iter2](){
        dowork(count2,value1,iter1,iter2);
    });
    dowork(count2,value1,iter2,iterEnd);


    c.join();
    d.join();
    printcount.join();

    cout<<value<<endl;
    cout<<"count  "<<count.getcount()<<endl;
    cout<<"count 1 "<<count2.getcount()<<endl;
    cout<<value1<<endl;



    return 0;

}

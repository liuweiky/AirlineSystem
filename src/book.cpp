#include "book.h"

book::book()
{
    //ctor
}

book::~book()
{
    //dtor
}
book::book(int leftticket_num)
{   //string mDepartureCity,mArrivalCity;

    cout<<"请输入出发城市"<<endl;
    cin>>mDepartureCity;
    cout<<"请输入到达城市"<<endl;
    cin>>mArrivalCity;
    if(1)
    {
        cout<<"航班号"<<endl;
        cin>>mAirlineName;
        while(mAirlineName=="")
        {
            cout<<"航班号不能为空"<<endl;
        }
        while(mAirlineName!="")
        {


            cout<<"预订张数"<<endl;
            cin>>ticket_num;
            if(ticket_num>0&&ticket_num<leftticket_num) cout<<"预订成功"<<endl;

        }
    }


}

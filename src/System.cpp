#include "System.h"

System::System()
{
    mAirlineGraph=new AirlineGraph();
}

System::~System()
{
    //dtor
}


void System::InsertAirlineInfo()
{
    Airline* airline=new Airline();
    cout<<endl;
    cout<<"请输入航空公司："<<endl;
    cin>>airline->mCompany;
    cout<<"请输入航班号："<<endl;
    cin>>airline->mAirlineName;
    cout<<"请输入起飞时间："<<endl;
    cin>>airline->mDepartureTime;
    cout<<"请输入到达时间："<<endl;
    cin>>airline->mArrivalTime;
    cout<<"请输入起飞机场："<<endl;
    cin>>airline->mDepartureAirport;
    airline->mDepartureCity=mAirlineGraph->GetAirportLocation(airline->mDepartureAirport);
    cout<<"请输入到达机场："<<endl;
    cin>>airline->mArrivalAirport;
    airline->mArrivalCity=mAirlineGraph->GetAirportLocation(airline->mArrivalAirport);
    cout<<"请输入机型："<<endl;
    cin>>airline->mAirplaneModel;
    cout<<"请输入容量："<<endl;
    cin>>airline->mCapacity;
    cout<<"请输入当前乘客人数："<<endl;
    cin>>airline->mCapacity;
    if(airline->mCapacity<airline->mCurrentNumber)
    {
        cout<<"非法输入！容量小于当前乘客人数！"<<endl;
        return;
    }
    cout<<"请输入票价："<<endl;
    cin>>airline->mPrice;
    cout<<"请输入折扣（1000%）："<<endl;
    cin>>airline->mIntDiscount;
    mAirlineGraph->InsertAirline(airline);
}

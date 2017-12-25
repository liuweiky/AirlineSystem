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
    if(mAirlineGraph->FindAirlineByName(airline->mAirlineName)!=NULL)
    {
        cout<<"已存在该航班！"<<endl;
        return;
    }
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

void System::ShowAllAirlineToUser()
{
    mAirlineGraph->ShowAllAirlineToUser();
}

void System::ShowAirlineByAirport(int no)
{
    mAirlineGraph->ShowAirlineByAirport(no);
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}

void System::ShowAirlineByCity(string city)
{
    cout<<city;
    mAirlineGraph->ShowAirlineByCity(city);
}

void System::SearchAirline(string name)
{
    vector<Airline*>* vec=mAirlineGraph->FindAirlineByName(name);
    if(vec->size()==0)
    {
        cout<<endl<<"无记录！"<<endl;
    }
    else
    {
        cout<<endl<<"========================================================================================================================================================================"<<endl;
        cout<<"共有"<<vec->size()<<"个结果:"<<endl;
        for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
        {
            Airline* airline=(*it);
            cout<<endl;
            cout<<setw(12)<<"航班号:"<<airline->mAirlineName<<endl;
            cout<<setw(12)<<"航空公司:"<<airline->mCompany<<endl;
            cout<<setw(12)<<"出发地:"<<airline->mDepartureCity<<endl;
            cout<<setw(12)<<"起飞机场:"<<airline->mDepartureAirport<<endl;
            cout<<setw(12)<<"目的地:"<<airline->mArrivalCity<<endl;
            cout<<setw(12)<<"着陆机场:"<<airline->mArrivalAirport<<endl;
            cout<<setw(12)<<"起飞时间:"<<airline->mDepartureTime<<endl;
            cout<<setw(12)<<"抵达时间:"<<airline->mArrivalTime<<endl;
            cout<<setw(12)<<"机型:"<<airline->mAirplaneModel<<endl;
            cout<<setw(12)<<"票价:"<<airline->mPrice<<endl;
            cout<<setw(12)<<"折扣:"<<airline->mIntDiscount/1000.0<<endl;
            cout<<setw(12)<<"折后票价:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
            cout<<setw(12)<<"载客量:"<<airline->mCapacity<<endl;
            cout<<setw(12)<<"已售:"<<airline->mCurrentNumber<<endl;
            cout<<setw(12)<<"余票:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
            cout<<endl;
            cout<<"==========================================="<<endl;
        }
    }
}

void System::Book()
{

}

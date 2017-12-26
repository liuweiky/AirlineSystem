#ifndef AIRLINE_H
#define AIRLINE_H
#include <iostream>
#include <stdlib.h>
using namespace std;

class Airline
{
    public:
        Airline();
        virtual ~Airline();
        string mAirlineName;        //航班号
        string mCompany;            //航班公司
        string mDepartureAirport;   //起飞机场
        string mArrivalAirport;     //到达机场
        string mDepartureTime;      //起飞时间
        string mArrivalTime;        //到达时间
        string mAirplaneModel;      //机型
        string mDepartureCity;      //起飞城市
        string mArrivalCity;        //到达城市
        int mPrice;                 //价格
        int mIntDiscount;           //折扣
        int mCapacity;              //满载人数
        int mCurrentNumber;         //当前人数
        Airline* mNextAirline;      //下一航班
        int GetPriceAfterDiscount();
        int GetAirlineTimeStamp();
    protected:

    private:
};

#endif // AIRLINE_H

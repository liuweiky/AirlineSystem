#ifndef BOOKORDER_H
#define BOOKORDER_H
#include <string>

using namespace std;

class BookOrder
{
    public:
        BookOrder();
        virtual ~BookOrder();
        string mName;
        string mIdNumber;
        string mAirlineName;        //航班号
        string mCompany;            //航班公司
        string mDepartureCity;      //起飞城市
        string mDepartureAirport;   //起飞机场
        string mArrivalCity;        //到达城市
        string mArrivalAirport;     //到达机场
        string mDepartureTime;      //起飞时间
        string mArrivalTime;        //到达时间
        string mAirplaneModel;      //机型
        int mPrice;                 //价格
    protected:

    private:
};

#endif // BOOKORDER_H

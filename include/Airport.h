#ifndef AIRPORT_H
#define AIRPORT_H
#include <string>
#include <Airline.h>
using namespace std;

class Airport
{
    public:
        Airport();                  //构造函数
        virtual ~Airport();
        int No;                     //机场编号
        string mLocation;           //机场地点
        string mAirportName;        //机场名字
        string mShortName;          //机场缩写
        Airline* mAdjAirline;       //航线邻接顶点
    protected:

    private:
};

#endif // AIRPORT_H

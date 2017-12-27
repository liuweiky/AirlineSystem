#ifndef ROUTE_H
#define ROUTE_H
#include "Airline.h"
#include <iostream>
#include <iomanip>
#include <vector>

class Route
{
    public:
        Route();
        virtual ~Route();
        int mPrevNo;    //最近机场编号
        int mTotalCost; //路线总花费
        vector<Airline*> mAirlineVec;   //途经航线
        Route& operator=(const Route& r);   //重载 =
        void ShowRoute();   //显示航线
        bool CheckPass(string airport); //检查是否曾经经过了某个机场
        int GetRouteLength();   //获取转机次数
        int SumToatalCost();    //价格求和
    protected:

    private:
};

#endif // ROUTE_H

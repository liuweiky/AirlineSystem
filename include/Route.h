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
        int mPrevNo;
        int mTotalCost;
        vector<Airline*> mAirlineVec;
        Route& operator=(const Route& r);
        void ShowRoute();
        bool CheckPass(string airport); //检查是否曾经经过了某个机场
        int GetRouteLength();
        int SumToatalCost();
    protected:

    private:
};

#endif // ROUTE_H

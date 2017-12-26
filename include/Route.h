#ifndef ROUTE_H
#define ROUTE_H
#include "Airline.h"
#include <iostream>
#include <vector>

class Route
{
    public:
        Route();
        virtual ~Route();
        int prevNo;
        vector<Airline*> mAirlineVec;
        Route& operator=(const Route& r);
        void ShowRoute();
        bool CheckPass(string airport);
    protected:

    private:
};

#endif // ROUTE_H

#ifndef AIRPORT_H
#define AIRPORT_H
#include <string>
#include <Airline.h>
using namespace std;

class Airport
{
    public:
        Airport();
        virtual ~Airport();
        int No;
        string mLocation;
        string mAirportName;
        string mShortName;
        Airline* mAdjAirline;
    protected:

    private:
};

#endif // AIRPORT_H

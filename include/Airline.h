#ifndef AIRLINE_H
#define AIRLINE_H
#include <iostream>
using namespace std;

class Airline
{
    public:
        Airline();
        virtual ~Airline();
        string mAirlineName;
        string mCompany;
        string mDepartureAirport;
        string mArrivalAirport;
        string mDepartureTime;
        string mArrivalTime;
        string mAirplaneModel;
        string mDepartureCity;
        string mArrivalCity;
        int mPrice;
        int mIntDiscount;
        int mCapacity;
        int mCurrentNumber;
        Airline* mNextAirline;
    protected:

    private:
};

#endif // AIRLINE_H

#include "Airline.h"

Airline::Airline()
{
    mNextAirline=NULL;
    mAirportNo=-1;
}

Airline::~Airline()
{
    //dtor
}

int Airline::GetPriceAfterDiscount()
{
    return int(mPrice*(1-mIntDiscount/1000.0));
}

int Airline::GetAirlineDepartureTimeStamp()
{
    int pos=mDepartureTime.find_first_of(":");
    string hour=mDepartureTime.substr(0,pos+1);
    string min=mDepartureTime.substr(pos+1);
    int h=atoi(hour.c_str());
    int m=atoi(min.c_str());
    return h*60+m;
}

int Airline::GetAirlineArrivalTimeStamp()
{
    int pos=mArrivalTime.find_first_of(":");
    string hour=mArrivalTime.substr(0,pos+1);
    string min=mArrivalTime.substr(pos+1);
    int h=atoi(hour.c_str());
    int m=atoi(min.c_str());
    return h*60+m;
}

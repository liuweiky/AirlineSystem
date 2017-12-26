#include "Airline.h"

Airline::Airline()
{
    mNextAirline=NULL;
}

Airline::~Airline()
{
    //dtor
}

int Airline::GetPriceAfterDiscount()
{
    return int(mPrice*(1-mIntDiscount/1000.0));
}

int Airline::GetAirlineTimeStamp()
{
    int pos=mDepartureTime.find_first_of(":");
    string hour=mDepartureTime.substr(0,pos+1);
    string min=mDepartureTime.substr(pos+1);
    int h=atoi(hour.c_str());
    int m=atoi(min.c_str());
    return h*60+m;
}

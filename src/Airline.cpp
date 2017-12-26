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

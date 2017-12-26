#include "Route.h"

Route::Route()
{
    mPrevNo=-1;
}

Route::~Route()
{
    //dtor
}

Route& Route::operator=(const Route& r)
{
    vector<Airline*> v=r.mAirlineVec;
    for(vector<Airline*>::iterator it=v.begin(); it!=v.end(); it++)
    {
        mAirlineVec.push_back(*it);
    }
    mPrevNo=r.mPrevNo;
    return *this;
}

void Route::ShowRoute()
{
    for(vector<Airline*>::iterator it=mAirlineVec.begin(); it!=mAirlineVec.end(); it++)
    {
        cout<<'['<<(*it)->mAirlineName<<']';
        if(it!=mAirlineVec.end()-1)
        {
            cout<<"->";
        }
    }
}

bool Route::CheckPass(string airport)
{
    for(vector<Airline*>::iterator it=mAirlineVec.begin(); it!=mAirlineVec.end(); it++)
    {
        if((*it)->mDepartureAirport==airport||(*it)->mArrivalAirport==airport)
            return true;
    }
    return false;
}

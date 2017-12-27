#include "Route.h"

Route::Route()
{
    mPrevNo=-1;
    mTotalCost=0;
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
    mTotalCost=r.mTotalCost;
    return *this;
}

void Route::ShowRoute()
{
    cout.setf(ios::left);
    cout<<"×Ü·ÑÓÃ: "<<mTotalCost<<"\t";
    for(vector<Airline*>::iterator it=mAirlineVec.begin(); it!=mAirlineVec.end(); it++)
    {
        string outstr="["+(*it)->mArrivalCity+"-"+(*it)->mArrivalAirport+" "+(*it)->mAirlineName+/*(*it)->GetPriceAfterDiscount()+*/"]";
        cout<<setw(32)<<outstr;
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

int Route::GetRouteLength()
{
    return mAirlineVec.size();
}

int Route::SumToatalCost()
{
    for(vector<Airline*>::iterator it=mAirlineVec.begin(); it!=mAirlineVec.end(); it++)
    {
        mTotalCost+=(*it)->GetPriceAfterDiscount();
    }
    return mTotalCost;
}

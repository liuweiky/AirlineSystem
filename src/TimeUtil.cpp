#include "TimeUtil.h"

TimeUtil::TimeUtil()
{
    //ctor
}

TimeUtil::~TimeUtil()
{
    //dtor
}

int TimeUtil::GetTimeStamp(string time)
{
    int pos=time.find_first_of(":");
    string hour=time.substr(0,pos+1);
    string min=time.substr(pos+1);
    int h=atoi(hour.c_str());
    int m=atoi(min.c_str());
    return h*60+m;
}

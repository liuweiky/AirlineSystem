#include "Airport.h"

//构造函数
Airport::Airport()
{
    No=-1;                  //城市编号
    mAirportName="";        //机场名字
    mLocation="";           //机场地点
    mAdjAirline=NULL;       //航线
}

Airport::~Airport()
{
    //dtor
}

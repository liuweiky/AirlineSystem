#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"

class System
{
    public:
        System();
        virtual ~System();
        AirlineGraph* mAirlineGraph;
        void InsertAirlineInfo();   //插入航班信息
        void ShowAllAirlineToUser();    //预览已经建立的全部航线的相关信息
        void ShowAirlineByAirport(int no);  //预览某个机场的航班
        void ShowAirlineByCity(string city);    //预览某个城市的航班
    protected:

    private:
};

#endif // SYSTEM_H

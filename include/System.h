#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"
#include <fstream>

class System
{
    public:
        System();
        virtual ~System();
        AirlineGraph* mAirlineGraph;
        Array mBookArray;
        void InsertAirlineInfo();   //插入航班信息
        void ShowAllAirlineToUser();    //预览已经建立的全部航线的相关信息
        void ShowAirlineByAirport(int no);  //预览某个机场的航班
        void ShowAirlineByCity(string city);    //预览某个城市的航班
        void SearchAirline(string name);    //通过航班号查看详细信息
        void Book();    //订票
    protected:

    private:
};

#endif // SYSTEM_H

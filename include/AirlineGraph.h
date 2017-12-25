#ifndef AIRLINEGRAPH_H
#define AIRLINEGRAPH_H
#include "Airport.h"
#include "Airline.h"
#include "jsonxx.h"
#include <fstream>
#include <iomanip>

using std::setw;
using namespace jsonxx;

//航线图
class AirlineGraph
{
    public:
        AirlineGraph();
        virtual ~AirlineGraph();
        int mAirportNumber;                 //机场编号
        int mAirlineNumber;                 //航线编号
        Airport** mAirportHeadArray;        //机场头指针
        Airline** mAirlineArray;            //航线头指针
        Airport* FindAirportByName(string name);
        void InsertAirline(Airport* airport,Airline* airline);
        void ShowAirlineGraph();            //展示航线
        void WriteAirlineJson();            //写入json
        void FindByAirlineName(string name);//通过航班号查找
    protected:

    private:
        Array GenerateAirlineJson();
        void LoadAirport();                 //读入机场
        void LoadAirline();                 //读入航线
};

#endif // AIRLINEGRAPH_H

#ifndef AIRLINEGRAPH_H
#define AIRLINEGRAPH_H
#include "Airport.h"
#include "Airline.h"
#include "jsonxx.h"
#include <fstream>
#include <iomanip>
#include <vector>

using std::setw;
using namespace jsonxx;

//航线图
class AirlineGraph
{
    public:
        AirlineGraph();
        virtual ~AirlineGraph();
        int mAirportNumber; //机场数量
        Airport** mAirportHeadArray;    //顶点表
        vector<Airline*>* mAirlineVector;   //保存航线
        Airport* FindAirportByName(string name);    //查找机场，获取指针
        int GetAirlineNumber(); //返回航线数目
        void InsertAirline(Airline* airline);   //外部插入接口
        void ShowAirlineGraph();    //打印输出边链表
        void WriteAirlineJson();    //写json到文件
        string GetAirportLocation(string airportName);
		
		
        void FindByAirlineName(string name);//通过航班号查找
        void SortByPrize(string name1,string name2);//按时间排序
        void SortByTime(string name1,string name2);//按时间排序
    protected:

    private:
        Array GenerateAirlineJson();    //生成json
        void LoadAirport(); //从本地载入机场数据
        void LoadAirline(); //从本地载入航线数据
        void InsertAirlineGraph(Airport* airport,Airline* airline); //在图中插入边（插入航线）
};

#endif // AIRLINEGRAPH_H

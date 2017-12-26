#ifndef AIRLINEGRAPH_H
#define AIRLINEGRAPH_H
#include "Airport.h"
#include "Airline.h"
#include "jsonxx.h"
#include "BookOrder.h"
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
        Airport* GetAirportByName(string name);    //查找机场，获取指针
        int GetAirlineNumber(); //返回航线数目
        void InsertAirline(Airline* airline);   //外部插入接口
        void ShowAllAirlineToUser();    //预览已经建立的全部航线的相关信息
        void ShowAirlineByAirport(int no);  //预览某个机场的航班
        void ShowAirlineByCity(string city);    //预览某个城市的航班
        void ShowAirlineGraph();    //打印输出边链表
        void WriteAirlineJson();    //写json到文件
        void Book(Airline* airline);    //接收外部订票信息，更新余票
        void Unsubscribe(BookOrder* bookOrder); //接收外部退订信息，更新余票
        vector<int>* GetAirportIdByLocation(string loc);    //通过城市获取该城市所有机场的Id
        string GetAirportLocation(string airportName);  //获得机场所在城市
        vector<Airline*>* FindAirlineByName(string name);//通过航班号查找
        vector<Airline*>* GetAirlineByDACity(string departure,string arrival);
        void ShowDACityAirlineByDiscountPrice(string departure,string arrival);
        void ShowDACityAirlineByDepartureTime(string departure,string arrival);
    protected:

    private:
        Array GenerateAirlineJson();    //生成json
        void LoadAirport(); //从本地载入机场数据
        void LoadAirline(); //从本地载入航线数据
        void InsertAirlineGraph(Airport* airport,Airline* airline); //在图中插入边（插入航线）
};

#endif // AIRLINEGRAPH_H

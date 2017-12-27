#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"
#include "BookOrder.h"
#include "TimeUtil.h"
#include <fstream>
#include <time.h>

class System
{
    public:
        System();
        virtual ~System();
        void InsertAirlineInfo();   //插入航班信息
        void RemoveAirline();   //删除航线
        void ShowWelcome();
        void ShowAllAirlineToUser();    //预览已经建立的全部航线的相关信息
        void ShowAirlineByAirport(int no);  //预览某个机场的航班
        void ShowAirlineByCity(string city);    //预览某个城市的航班
        void SearchAirlineByName(string name);    //通过航班号查看详细信息
        void Book();    //订票
        void ShowBookList();
        void Unsubscribe(); //退票
        void UnsubscribeByName(string name); //通过姓名退票
        void UnsubscribeByIdNum(string Id); //通过证件号退票
        void UnsubscribeByNo(int no); //通过序号退票
        void MenuDaemon();  //菜单守护函数
        void ShowAdvisableRoute(string departureCity,string arrivalCity,string departureTime,string arrivalTime);   //显示合理路线
        void ShowBestAirlineNetwork(string departureCity);  //显示最优航线网络
        void RecommandBestRoute(string departureCity,string arrivalCity);   //推荐航线
    protected:

    private:
        AirlineGraph* mAirlineGraph;    //航线图
        vector<BookOrder*>* mBookOrderVector;   //保存订单
        void LoadBookOrder();   //本地加载订单
        int GetBookOrderNum();  //订单数目
        Array GenerateBookJson();    //生成json
        void ShowMenu(int i);   //显示菜单
};

#endif // SYSTEM_H

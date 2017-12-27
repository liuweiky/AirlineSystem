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
        void MenuDaemon();
        void ShowAdvisableRoute(string departureCity,string arrivalCity,string departureTime,string arrivalTime);
        void ShowBestAirlineNetwork(string departureCity);
        void RecommandBestRoute(string departureCity,string arrivalCity);
    protected:

    private:
        AirlineGraph* mAirlineGraph;
        vector<BookOrder*>* mBookOrderVector;
        void LoadBookOrder();
        int GetBookOrderNum();
        Array GenerateBookJson();    //生成json
        void ShowMenu(int i);
};

#endif // SYSTEM_H

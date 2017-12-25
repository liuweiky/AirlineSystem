#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"
#include "BookOrder.h"
#include <fstream>

class System
{
    public:
        System();
        virtual ~System();
        AirlineGraph* mAirlineGraph;
        vector<BookOrder*>* mBookOrderVector;
        void InsertAirlineInfo();   //插入航班信息
        void ShowAllAirlineToUser();    //预览已经建立的全部航线的相关信息
        void ShowAirlineByAirport(int no);  //预览某个机场的航班
        void ShowAirlineByCity(string city);    //预览某个城市的航班
        void SearchAirline(string name);    //通过航班号查看详细信息
        void LoadBookOrder();
        int GetBookOrderNum();
        void Book();    //订票
        void ShowBookList();
        void Unsubscribe(); //退票
        void UnsubscribeByName(string name); //通过姓名退票
        void UnsubscribeByIdNum(string Id); //通过证件号退票
        void UnsubscribeByNo(int no); //通过序号退票
    protected:

    private:
        Array GenerateBookJson();    //生成json
};

#endif // SYSTEM_H

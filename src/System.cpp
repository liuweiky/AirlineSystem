#include "System.h"

System::System()
{
    cout.setf(ios::left);
    ShowWelcome();
    mAirlineGraph=new AirlineGraph();
    cout<<endl<<"机场航线数据加载完毕……"<<endl;
    mBookOrderVector=NULL;
    LoadBookOrder();
    cout<<"订单数据加载完毕……"<<endl;
    MenuDaemon();
}

System::~System()
{
    //dtor
}

void System::ShowWelcome()
{
    cout<<"欢迎使用机票预定系统！"<<endl;
    time_t timep;
    time (&timep);
    char timestr[64];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S",localtime(&timep));
    cout<<"登录时间："<<timestr<<endl;
}

void System::LoadBookOrder()
{
    ifstream infile;
    string s;
    infile.open("data/Book.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    infile.close();
    s=tmp.str();
    Array BookArray;
    BookArray.parse(s);  //解析json
    if(mBookOrderVector!=NULL)
    {
        delete mBookOrderVector;
    }
    mBookOrderVector=new vector<BookOrder*>();
    for(int i=0;i<BookArray.size();i++)  //保存航线到vector
    {
        BookOrder* bookOrder=new BookOrder();
        bookOrder->mName=BookArray.get<Object>(i).get<String>("姓名");
        bookOrder->mIdNumber=BookArray.get<Object>(i).get<String>("证件号");
        bookOrder->mAirlineName=BookArray.get<Object>(i).get<String>("航班号");
        bookOrder->mCompany=BookArray.get<Object>(i).get<String>("公司");
        bookOrder->mDepartureAirport=BookArray.get<Object>(i).get<String>("起飞机场");
        bookOrder->mArrivalAirport=BookArray.get<Object>(i).get<String>("到达机场");
        bookOrder->mDepartureTime=BookArray.get<Object>(i).get<String>("起飞时间");
        bookOrder->mArrivalTime=BookArray.get<Object>(i).get<String>("到达时间");
        bookOrder->mAirplaneModel=BookArray.get<Object>(i).get<String>("机型");
        bookOrder->mDepartureCity=BookArray.get<Object>(i).get<String>("起始城市");
        bookOrder->mArrivalCity=BookArray.get<Object>(i).get<String>("到达城市");
        bookOrder->mPrice=BookArray.get<Object>(i).get<Number>("购买价格");
        mBookOrderVector->push_back(bookOrder);
    }
}

void System::InsertAirlineInfo()
{
    Airline* airline=new Airline();
    cout<<endl;
    cout<<"请输入航空公司："<<endl;
    cin>>airline->mCompany;
    cout<<"请输入航班号："<<endl;
    cin>>airline->mAirlineName;
    cout<<"请输入起飞时间："<<endl;
    cin>>airline->mDepartureTime;
    cout<<"请输入到达时间："<<endl;
    cin>>airline->mArrivalTime;
    cout<<"请输入起飞机场："<<endl;
    cin>>airline->mDepartureAirport;
    airline->mDepartureCity=mAirlineGraph->GetAirportLocation(airline->mDepartureAirport);
    cout<<"请输入到达机场："<<endl;
    cin>>airline->mArrivalAirport;
    airline->mArrivalCity=mAirlineGraph->GetAirportLocation(airline->mArrivalAirport);
    cout<<"请输入机型："<<endl;
    cin>>airline->mAirplaneModel;
    cout<<"请输入容量："<<endl;
    cin>>airline->mCapacity;
    cout<<"请输入当前乘客人数："<<endl;
    cin>>airline->mCurrentNumber;
    if(airline->mCapacity<airline->mCurrentNumber)
    {
        cout<<"非法输入！容量小于当前乘客人数！"<<endl;
        return;
    }
    cout<<"请输入票价："<<endl;
    cin>>airline->mPrice;
    cout<<"请输入折扣（1000%）："<<endl;
    cin>>airline->mIntDiscount;
    mAirlineGraph->InsertAirline(airline);
    cout<<endl<<"航班"<<airline->mAirlineName<<"录入成功！"<<endl;
}

void System::RemoveAirline()
{
    cout<<endl<<"请输入航班号："<<endl;
    string name;
    cin>>name;
    vector<Airline*>* vec=mAirlineGraph->FindAirlineByName(name);
    if(vec->size()==0)
    {
        cout<<endl<<"无记录！"<<endl;
        return;
    }else if(vec->size()==1)
    {
        mAirlineGraph->RemoveAirline((*vec)[0]);
        cout<<endl<<"航班"<<name<<"已删除！"<<endl;
    }else
    {
        cout<<endl<<"==========================================="<<endl;
        cout<<"共有"<<vec->size()<<"个结果:"<<endl;
        for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
        {
            cout<<"【"<<it-vec->begin()+1<<"】"<<endl;
            Airline* airline=(*it);
            cout<<endl;
            cout<<setw(12)<<"航班号:"<<airline->mAirlineName<<endl;
            cout<<setw(12)<<"航空公司:"<<airline->mCompany<<endl;
            cout<<setw(12)<<"出发地:"<<airline->mDepartureCity<<endl;
            cout<<setw(12)<<"起飞机场:"<<airline->mDepartureAirport<<endl;
            cout<<setw(12)<<"目的地:"<<airline->mArrivalCity<<endl;
            cout<<setw(12)<<"着陆机场:"<<airline->mArrivalAirport<<endl;
            cout<<setw(12)<<"起飞时间:"<<airline->mDepartureTime<<endl;
            cout<<setw(12)<<"抵达时间:"<<airline->mArrivalTime<<endl;
            cout<<setw(12)<<"机型:"<<airline->mAirplaneModel<<endl;
            cout<<setw(12)<<"票价:"<<airline->mPrice<<endl;
            cout<<setw(12)<<"折扣:"<<airline->mIntDiscount/1000.0<<endl;
            cout<<setw(12)<<"折后票价:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
            cout<<setw(12)<<"载客量:"<<airline->mCapacity<<endl;
            cout<<setw(12)<<"已售:"<<airline->mCurrentNumber<<endl;
            cout<<setw(12)<<"余票:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
            cout<<endl;
            cout<<"==========================================="<<endl;
        }

        cout<<"你是想删除？（请输入数字）"<<endl;
        int i;
        cin>>i;
        while(i>vec->size()||i<=0)
        {
            cout<<endl<<"输入不合法，请重新输入！"<<endl;
            cin>>i;
        }
        mAirlineGraph->RemoveAirline((*vec)[i-1]);
        cout<<endl<<"航班"<<name<<"已删除！"<<endl;
    }
}

void System::ShowAllAirlineToUser()
{
    mAirlineGraph->ShowAllAirlineToUser();
}

void System::ShowAirlineByAirport(int no)
{
    mAirlineGraph->ShowAirlineByAirport(no);
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}

void System::ShowAirlineByCity(string city)
{
    cout<<city;
    mAirlineGraph->ShowAirlineByCity(city);
}

void System::SearchAirlineByName(string name)
{
    vector<Airline*>* vec=mAirlineGraph->FindAirlineByName(name);
    if(vec->size()==0)
    {
        cout<<endl<<"无记录！"<<endl;
    }
    else
    {
        cout<<endl<<"==========================================="<<endl;
        cout<<"共有"<<vec->size()<<"个结果:"<<endl;
        for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
        {
            Airline* airline=(*it);
            cout<<endl;
            cout<<setw(12)<<"航班号:"<<airline->mAirlineName<<endl;
            cout<<setw(12)<<"航空公司:"<<airline->mCompany<<endl;
            cout<<setw(12)<<"出发地:"<<airline->mDepartureCity<<endl;
            cout<<setw(12)<<"起飞机场:"<<airline->mDepartureAirport<<endl;
            cout<<setw(12)<<"目的地:"<<airline->mArrivalCity<<endl;
            cout<<setw(12)<<"着陆机场:"<<airline->mArrivalAirport<<endl;
            cout<<setw(12)<<"起飞时间:"<<airline->mDepartureTime<<endl;
            cout<<setw(12)<<"抵达时间:"<<airline->mArrivalTime<<endl;
            cout<<setw(12)<<"机型:"<<airline->mAirplaneModel<<endl;
            cout<<setw(12)<<"票价:"<<airline->mPrice<<endl;
            cout<<setw(12)<<"折扣:"<<airline->mIntDiscount/1000.0<<endl;
            cout<<setw(12)<<"折后票价:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
            cout<<setw(12)<<"载客量:"<<airline->mCapacity<<endl;
            cout<<setw(12)<<"已售:"<<airline->mCurrentNumber<<endl;
            cout<<setw(12)<<"余票:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
            cout<<endl;
            cout<<"==========================================="<<endl;
        }
    }
}

void System::Book()
{
    string name;
    cout<<endl<<"请输入航班号："<<endl;
    cin>>name;

    vector<Airline*>* vec=mAirlineGraph->FindAirlineByName(name);
    if(vec->size()==0)
    {
        cout<<endl<<"无记录！"<<endl;
        return;
    }
    else if(vec->size()==1)
    {
        Airline* airline=(*vec)[0];

        cout<<"==========================================="<<endl;
        cout<<endl;
        cout<<setw(12)<<"航班号:"<<airline->mAirlineName<<endl;
        cout<<setw(12)<<"航空公司:"<<airline->mCompany<<endl;
        cout<<setw(12)<<"出发地:"<<airline->mDepartureCity<<endl;
        cout<<setw(12)<<"起飞机场:"<<airline->mDepartureAirport<<endl;
        cout<<setw(12)<<"目的地:"<<airline->mArrivalCity<<endl;
        cout<<setw(12)<<"着陆机场:"<<airline->mArrivalAirport<<endl;
        cout<<setw(12)<<"起飞时间:"<<airline->mDepartureTime<<endl;
        cout<<setw(12)<<"抵达时间:"<<airline->mArrivalTime<<endl;
        cout<<setw(12)<<"机型:"<<airline->mAirplaneModel<<endl;
        cout<<setw(12)<<"票价:"<<airline->mPrice<<endl;
        cout<<setw(12)<<"折扣:"<<airline->mIntDiscount/1000.0<<endl;
        cout<<setw(12)<<"折后票价:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
        cout<<setw(12)<<"载客量:"<<airline->mCapacity<<endl;
        cout<<setw(12)<<"已售:"<<airline->mCurrentNumber<<endl;
        cout<<setw(12)<<"余票:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;


        if(airline->mCapacity==airline->mCurrentNumber)
        {
            cout<<endl<<"已售空！"<<endl;
            return;
        }
        Object jsonObj;
        string s1,s2;
        cout<<endl<<"请输入姓名："<<endl;
        cin>>s1;
        jsonObj<<"姓名"<<s1;
        cout<<endl<<"请输入证件号："<<endl;
        cin>>s2;
        jsonObj<<"证件号"<<s2;

        jsonObj<<"公司"<<airline->mCompany;
        jsonObj<<"航班号"<<airline->mAirlineName;
        jsonObj<<"起始城市"<<airline->mDepartureCity;
        jsonObj<<"起飞机场"<<airline->mDepartureAirport;
        jsonObj<<"到达城市"<<airline->mArrivalCity;
        jsonObj<<"到达机场"<<airline->mArrivalAirport;
        jsonObj<<"起飞时间"<<airline->mDepartureTime;
        jsonObj<<"到达时间"<<airline->mArrivalTime;
        jsonObj<<"机型"<<airline->mAirplaneModel;
        jsonObj<<"购买价格"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0));

        cout<<"==========================================="<<endl;
        cout<<endl;
        cout<<"================ 预订成功 ================="<<endl;
        cout<<endl;
        cout<<setw(12)<<"姓名:"<<s1<<endl;
        cout<<setw(12)<<"证件号:"<<s2<<endl;
        cout<<setw(12)<<"航班号:"<<airline->mAirlineName<<endl;
        cout<<setw(12)<<"航空公司:"<<airline->mCompany<<endl;
        cout<<setw(12)<<"出发地:"<<airline->mDepartureCity<<endl;
        cout<<setw(12)<<"起飞机场:"<<airline->mDepartureAirport<<endl;
        cout<<setw(12)<<"目的地:"<<airline->mArrivalCity<<endl;
        cout<<setw(12)<<"着陆机场:"<<airline->mArrivalAirport<<endl;
        cout<<setw(12)<<"起飞时间:"<<airline->mDepartureTime<<endl;
        cout<<setw(12)<<"抵达时间:"<<airline->mArrivalTime<<endl;
        cout<<setw(12)<<"机型:"<<airline->mAirplaneModel<<endl;
        cout<<setw(12)<<"购买价格:"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0))<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;

        Array bookArray=GenerateBookJson();
        bookArray<<jsonObj;
        //cout<<bookArray.json();

        ofstream outfile;
        outfile.open("data/Book.json");

        outfile<<bookArray.json();
        outfile.close();

        mAirlineGraph->Book(airline);

        LoadBookOrder();
    }
    else if(vec->size()>1)
    {
        cout<<"共有"<<vec->size()<<"个结果:"<<endl;
        cout<<"==========================================="<<endl;
        for(int i=0;i<vec->size();i++)
        {
            Airline* airline=(*vec)[i];
            cout<<"【"<<i+1<<"】"<<endl;
            cout<<endl;
            cout<<setw(12)<<"航班号:"<<airline->mAirlineName<<endl;
            cout<<setw(12)<<"航空公司:"<<airline->mCompany<<endl;
            cout<<setw(12)<<"出发地:"<<airline->mDepartureCity<<endl;
            cout<<setw(12)<<"起飞机场:"<<airline->mDepartureAirport<<endl;
            cout<<setw(12)<<"目的地:"<<airline->mArrivalCity<<endl;
            cout<<setw(12)<<"着陆机场:"<<airline->mArrivalAirport<<endl;
            cout<<setw(12)<<"起飞时间:"<<airline->mDepartureTime<<endl;
            cout<<setw(12)<<"抵达时间:"<<airline->mArrivalTime<<endl;
            cout<<setw(12)<<"机型:"<<airline->mAirplaneModel<<endl;
            cout<<setw(12)<<"票价:"<<airline->mPrice<<endl;
            cout<<setw(12)<<"折扣:"<<airline->mIntDiscount/1000.0<<endl;
            cout<<setw(12)<<"折后票价:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
            cout<<setw(12)<<"载客量:"<<airline->mCapacity<<endl;
            cout<<setw(12)<<"已售:"<<airline->mCurrentNumber<<endl;
            cout<<setw(12)<<"余票:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
            cout<<endl;
            cout<<"==========================================="<<endl;
        }

        cout<<"你是想预订？（请输入数字）"<<endl;
        int i;
        cin>>i;
        while(i>vec->size()||i<=0)
        {
            cout<<endl<<"输入不合法，请重新输入！"<<endl;
            cin>>i;
        }
        Airline* airline=(*vec)[i-1];

        if(airline->mCapacity==airline->mCurrentNumber)
        {
            cout<<endl<<"已售空！"<<endl;
            return;
        }
        Object jsonObj;
        string s1,s2;
        cout<<endl<<"请输入姓名："<<endl;
        cin>>s1;
        jsonObj<<"姓名"<<s1;
        cout<<endl<<"请输入证件号："<<endl;
        cin>>s2;
        jsonObj<<"证件号"<<s2;

        jsonObj<<"公司"<<airline->mCompany;
        jsonObj<<"航班号"<<airline->mAirlineName;
        jsonObj<<"起始城市"<<airline->mDepartureCity;
        jsonObj<<"起飞机场"<<airline->mDepartureAirport;
        jsonObj<<"到达城市"<<airline->mArrivalCity;
        jsonObj<<"到达机场"<<airline->mArrivalAirport;
        jsonObj<<"起飞时间"<<airline->mDepartureTime;
        jsonObj<<"到达时间"<<airline->mArrivalTime;
        jsonObj<<"机型"<<airline->mAirplaneModel;
        jsonObj<<"购买价格"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0));

        cout<<"==========================================="<<endl;
        cout<<endl;
        cout<<"================ 预订成功 ================="<<endl;
        cout<<endl;
        cout<<setw(12)<<"姓名:"<<s1<<endl;
        cout<<setw(12)<<"证件号:"<<s2<<endl;
        cout<<setw(12)<<"航班号:"<<airline->mAirlineName<<endl;
        cout<<setw(12)<<"航空公司:"<<airline->mCompany<<endl;
        cout<<setw(12)<<"出发地:"<<airline->mDepartureCity<<endl;
        cout<<setw(12)<<"起飞机场:"<<airline->mDepartureAirport<<endl;
        cout<<setw(12)<<"目的地:"<<airline->mArrivalCity<<endl;
        cout<<setw(12)<<"着陆机场:"<<airline->mArrivalAirport<<endl;
        cout<<setw(12)<<"起飞时间:"<<airline->mDepartureTime<<endl;
        cout<<setw(12)<<"抵达时间:"<<airline->mArrivalTime<<endl;
        cout<<setw(12)<<"机型:"<<airline->mAirplaneModel<<endl;
        cout<<setw(12)<<"购买价格:"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0))<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;

        Array bookArray=GenerateBookJson();
        bookArray<<jsonObj;
        //cout<<bookArray.json();

        ofstream outfile;
        outfile.open("data/Book.json");

        outfile<<bookArray.json();
        outfile.close();

        mAirlineGraph->Book(airline);

        LoadBookOrder();
    }
}

int System::GetBookOrderNum()
{
    return mBookOrderVector->size();
}

Array System::GenerateBookJson()
{
    Array jsonArray;
    for(int i=0; i<GetBookOrderNum(); i++)
    {
        BookOrder* bookOrder=(*mBookOrderVector)[i];
        Object jsonObj;
        jsonObj<<"姓名"<<bookOrder->mName;
        jsonObj<<"证件号"<<bookOrder->mIdNumber;
        jsonObj<<"航班号"<<bookOrder->mAirlineName;
        jsonObj<<"公司"<<bookOrder->mCompany;
        jsonObj<<"起飞机场"<<bookOrder->mDepartureAirport;
        jsonObj<<"到达机场"<<bookOrder->mArrivalAirport;
        jsonObj<<"起飞时间"<<bookOrder->mDepartureTime;
        jsonObj<<"到达时间"<<bookOrder->mArrivalTime;
        jsonObj<<"起始城市"<<bookOrder->mDepartureCity;
        jsonObj<<"到达城市"<<bookOrder->mArrivalCity;
        jsonObj<<"机型"<<bookOrder->mAirplaneModel;
        jsonObj<<"购买价格"<<bookOrder->mPrice;

        jsonArray<<jsonObj;
    }
    return jsonArray;
}

void System::ShowBookList()
{
    cout<<endl;
    for(int i=0;i<mBookOrderVector->size();i++)
    {
        BookOrder* bookOrder=(*mBookOrderVector)[i];
        cout<<"==========================================="<<endl;
        cout<<"【"<<i+1<<"】"<<endl;
        cout<<endl;
        cout<<setw(12)<<"姓名:"<<bookOrder->mName<<endl;
        cout<<setw(12)<<"证件号:"<<bookOrder->mIdNumber<<endl;
        cout<<setw(12)<<"航班号:"<<bookOrder->mAirlineName<<endl;
        cout<<setw(12)<<"航空公司:"<<bookOrder->mCompany<<endl;
        cout<<setw(12)<<"出发地:"<<bookOrder->mDepartureCity<<endl;
        cout<<setw(12)<<"起飞机场:"<<bookOrder->mDepartureAirport<<endl;
        cout<<setw(12)<<"目的地:"<<bookOrder->mArrivalCity<<endl;
        cout<<setw(12)<<"着陆机场:"<<bookOrder->mArrivalAirport<<endl;
        cout<<setw(12)<<"起飞时间:"<<bookOrder->mDepartureTime<<endl;
        cout<<setw(12)<<"抵达时间:"<<bookOrder->mArrivalTime<<endl;
        cout<<setw(12)<<"机型:"<<bookOrder->mAirplaneModel<<endl;
        cout<<setw(12)<<"购买价格:"<<bookOrder->mPrice<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;
    }
}

void System::Unsubscribe()
{
    ShowBookList();
    cout<<endl<<"【1】通过姓名退票"<<endl<<"【2】通过证件号退票"<<endl<<"【3】通过以上序号退票"<<endl;
    int i;
    cin>>i;
    while(i>3||i<1)
    {
        cout<<endl<<"输入不合法，请重新输入！"<<endl;
        cin>>i;
    }
    string s;
    switch(i)
    {
    case 1:
        cout<<endl<<"请输入姓名："<<endl;
        cin>>s;
        UnsubscribeByName(s);
        break;
    case 2:
        cout<<endl<<"请输入证件号："<<endl;
        cin>>s;
        UnsubscribeByIdNum(s);
        break;
    case 3:
        cout<<endl<<"请输入以上序号："<<endl;
        cin>>i;
        while(i>GetBookOrderNum()||i<=0)
        {
            cout<<endl<<"输入不合法，请重新输入！"<<endl;
            cin>>i;
        }
        UnsubscribeByNo(i);
        break;
    }

    Array bookArray=GenerateBookJson();
    //cout<<bookArray.json();

    ofstream outfile;
    outfile.open("data/Book.json");

    outfile<<bookArray.json();
    outfile.close();

    LoadBookOrder();
}

void System::UnsubscribeByName(string name)
{
    vector<BookOrder*>::iterator it;
    for(it=mBookOrderVector->begin();it!=mBookOrderVector->end();it++)
    {
        if((*it)->mName==name)
        {
            mAirlineGraph->Unsubscribe(*it);    //必须先在图里取消订单！下面也是！否则删除后迭代器会指向后一个元素
            mBookOrderVector->erase(it);
            break;
        }
    }
    if(it==mBookOrderVector->end())
    {
        cout<<endl<<"无记录！"<<endl;
    }
}

void System::UnsubscribeByIdNum(string Id)
{
    vector<BookOrder*>::iterator it;
    for(it=mBookOrderVector->begin();it!=mBookOrderVector->end();it++)
    {
        if((*it)->mIdNumber==Id)
        {
            mAirlineGraph->Unsubscribe(*it);
            mBookOrderVector->erase(it);
            break;
        }
    }
    if(it==mBookOrderVector->end())
    {
        cout<<endl<<"无记录！"<<endl;
    }
}

void System::UnsubscribeByNo(int no)
{
    vector<BookOrder*>::iterator it=mBookOrderVector->begin();
    mAirlineGraph->Unsubscribe(*(it+no-1));
    mBookOrderVector->erase(it+no-1);
}

void System::ShowAdvisableRoute(string departureCity,string arrivalCity,string departureTime,string arrivalTime)
{
    TimeUtil timeUtil;
    int dTime=timeUtil.GetTimeStamp(departureTime);
    int aTime=timeUtil.GetTimeStamp(arrivalTime);
    vector<Route*>* vec=mAirlineGraph->GetAdvisableRouteWithBFS(departureCity,arrivalCity,dTime,aTime);
    if(vec->size()==0)
    {
        cout<<endl<<"抱歉，无可行航线"<<endl;
    }else
    {
        cout<<endl<<"========================================================================================================================================================================"<<endl;
        for(vector<Route*>::iterator it=vec->begin(); it!=vec->end(); it++)
        {
            cout<<endl;
            (*it)->ShowRoute();
        }
        cout<<endl<<endl<<"========================================================================================================================================================================"<<endl;
    }
}

void System::ShowBestAirlineNetwork(string departureCity)
{
    vector<int>* vec=mAirlineGraph->GetAirportIdByLocation(departureCity);
    if(vec->size()==0)
    {
        cout<<endl<<"抱歉，该城市暂无可行航线"<<endl;
    }
    for(int j=0; j<vec->size(); j++)
    {
        cout<<endl<<"========================================================================================================================================================================"<<endl;
        cout<<endl<<"从【"<<departureCity<<" - "<<mAirlineGraph->mAirportHeadArray[(*vec)[j]]->mAirportName<<"】到："<<endl<<endl;
        Route** r=mAirlineGraph->Dijkstra((*vec)[j]);   //调用 Dijkstra 算法
        for(int i=0; i<mAirlineGraph->mAirportNumber; i++)
        {
            string outstr="【"+mAirlineGraph->mAirportHeadArray[i]->mLocation+" - "+mAirlineGraph->mAirportHeadArray[i]->mAirportName+"】";
            if(r[i]!=NULL)
            {
                cout<<setw(30)<<outstr;
                Route* route=r[i];
                route->SumToatalCost();
                route->ShowRoute();
                cout<<endl;
            }
            else
            {
                cout<<setw(30)<<outstr<<"NULL"<<endl;
            }
        }
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;

}

void System::RecommandBestRoute(string departureCity,string arrivalCity)
{

    vector<int>* dVec=mAirlineGraph->GetAirportIdByLocation(departureCity);
    vector<int>* aVec=mAirlineGraph->GetAirportIdByLocation(arrivalCity);
    if(dVec->size()==0||aVec->size()==0)
    {
        cout<<endl<<"抱歉，无可行航线"<<endl;
        return;
    }
    Route* routeArray[dVec->size()][aVec->size()];
    for(int i=0;i<dVec->size();i++)
    {
        for(int j=0;j<aVec->size();j++)
        {
            Route** r=mAirlineGraph->Dijkstra((*dVec)[i]);   //调用 Dijkstra 算法
            r[(*aVec)[j]]->SumToatalCost();
            routeArray[i][j]=r[(*aVec)[j]];
        }
    }
    Route* best=routeArray[0][0];
    for(int i=0;i<dVec->size();i++)
    {
        for(int j=0;j<aVec->size();j++)
        {
            if(routeArray[i][j]->mTotalCost<best->mTotalCost)
            best=routeArray[i][j];
        }
    }
    cout<<endl;
    best->ShowRoute();
    cout<<endl;
}

void System::MenuDaemon()
{
    ShowMenu(0);

    int operation=0;
    cin>>operation;

    while(operation)
    {
        int x;
        string s1,s2,s3,s4;
        switch(operation)
        {
        case 1:
            InsertAirlineInfo();
            break;
        case 2:
            RemoveAirline();
            break;
        case 3:
            ShowAllAirlineToUser();
            break;
        case 4:
            ShowMenu(3);
            cin>>s1;
            SearchAirlineByName(s1);
            break;
        case 5:
            ShowBookList();
            break;
        case 6:
            Book();
            break;
        case 7:
            Unsubscribe();
            break;
        case 8:
            ShowMenu(1);
            cin>>x;
            if(x==1)
            {
                ShowMenu(2);
                cin>>s1>>s2;
                mAirlineGraph->ShowDACityAirlineByDepartureTime(s1,s2);
            }else if(x==2)
            {
                ShowMenu(2);
                cin>>s1>>s2;
                mAirlineGraph->ShowDACityAirlineByDiscountPrice(s1,s2);
            }
            break;
        case 9:
            ShowMenu(4);
            cin>>s1>>s2>>s3>>s4;
            ShowAdvisableRoute(s1,s2,s3,s4);
            break;
        case 10:
            ShowMenu(5);
            cin>>s1;
            ShowBestAirlineNetwork(s1);
            break;
        case 11:
            ShowMenu(6);
            cin>>s1>>s2;
            RecommandBestRoute(s1,s2);
            break;
        }
        ShowMenu(0);
        cin>>operation;
    }
}

void System::ShowMenu(int i)
{
    switch(i)
    {
    case 0:
        cout<<endl
        <<"1) 录入航线"<<endl
        <<"2) 删除航线"<<endl
        <<"3) 浏览全部航线（！！！慎用，4000多条，信息量略大！！！）"<<endl
        <<"4）航班号查询航线"<<endl
        <<"5）查看订单情况"<<endl
        <<"6）订票"<<endl
        <<"7）退票"<<endl
        <<"8）查询城间航线"<<endl
        <<"9）合理线路设计"<<endl
        <<"10）航线网络"<<endl
        <<"11）推荐最优线路"<<endl
        <<endl
        <<"0）退出"<<endl;
        break;
    case 1:
        cout<<endl
        <<"请选择排序方式"<<endl
        <<"1）出发时间"<<endl
        <<"2）折后票价"<<endl
        <<"0）退出"<<endl;
        break;
    case 2:
        cout<<endl
        <<"请输入出发城市和到达城市："<<endl;
        break;
    case 3:
        cout<<endl
        <<"请输入航班号："<<endl;
        break;
    case 4:
        cout<<endl
        <<"请输入出发城市、到达城市、出发时间和到达时间："<<endl;
        break;
    case 5:
        cout<<endl
        <<"请输入出发城市："<<endl;
        break;
    case 6:
        cout<<endl
        <<"请输入出发城市和到达城市："<<endl;
        break;
    }
}

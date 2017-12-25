#include "AirlineGraph.h"

AirlineGraph::AirlineGraph()
{
    LoadAirport();
    LoadAirline();
   // ShowAirlineGraph();
    //WriteAirlineJson();
    Properline("杭州","长春");
    cout<<timetransform("08:00");

}

AirlineGraph::~AirlineGraph()
{
    //dtor
}
//读入机场信息
void AirlineGraph::LoadAirport()
{
    Array AirportArray;
    ifstream infile;
    string s;
    infile.open("Airport.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    s=tmp.str();
    AirportArray.parse(s);  //解析json
    mAirportNumber=AirportArray.size();
  //  cout<<mAirportNumber<<endl;
    mAirportHeadArray=new Airport*[mAirportNumber];
    for(int i=0;i<mAirportNumber;i++)   //生成顶点表
    {
        mAirportHeadArray[i]=new Airport();
        mAirportHeadArray[i]->No=AirportArray.get<Object>(i).get<Number>("序号");
        mAirportHeadArray[i]->mAirportName=AirportArray.get<Object>(i).get<String>("机场");
        mAirportHeadArray[i]->mShortName=AirportArray.get<Object>(i).get<String>("机场代号");
        mAirportHeadArray[i]->mLocation=AirportArray.get<Object>(i).get<String>("城市");
    }
    //cout<<AirportArray.json();
}
//读入航线信息
void AirlineGraph::LoadAirline()
{
    Array AirlineArray;
    ifstream infile;
    string s;
    infile.open("Airline.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    s=tmp.str();
    AirlineArray.parse(s);  //解析json
    mAirlineVector=new vector<Airline*>();
    for(int i=0;i<AirlineArray.size();i++)  //保存航线到vector
    {
        Airline* airline=new Airline();
        airline->mAirlineName=AirlineArray.get<Object>(i).get<String>("航班号");
        airline->mCompany=AirlineArray.get<Object>(i).get<String>("公司");
        airline->mDepartureAirport=AirlineArray.get<Object>(i).get<String>("起飞机场");
        airline->mArrivalAirport=AirlineArray.get<Object>(i).get<String>("到达机场");
        airline->mDepartureTime=AirlineArray.get<Object>(i).get<String>("起飞时间");
        airline->mArrivalTime=AirlineArray.get<Object>(i).get<String>("到达时间");
        airline->mAirplaneModel=AirlineArray.get<Object>(i).get<String>("机型");
        airline->mDepartureCity=AirlineArray.get<Object>(i).get<String>("起始城市");
        airline->mArrivalCity=AirlineArray.get<Object>(i).get<String>("到达城市");
        airline->mPrice=AirlineArray.get<Object>(i).get<Number>("价格");
        airline->mIntDiscount=AirlineArray.get<Object>(i).get<Number>("最大折扣");
        airline->mCapacity=AirlineArray.get<Object>(i).get<Number>("满载");
        airline->mCurrentNumber=AirlineArray.get<Object>(i).get<Number>("当前人数");
        mAirlineVector->push_back(airline);

        Airport* airport=FindAirportByName(airline->mDepartureAirport);
        if(airport!=NULL)   //判断机场是否存在
        {
            InsertAirlineGraph(airport,airline);    //插入到图
        }
    }
    infile.close();
    //cout<<AirlineArray.json();
}
//通过城市找机场
Airport* AirlineGraph::FindAirportByCity(string city)
{
    for(int i=0;i<mAirportNumber;i++)
    {
        if(mAirportHeadArray[i]->mLocation==city)
        {

          //  cout<<mAirportHeadArray[i]->mAirportName;
            return mAirportHeadArray[i];
        }
    }
    return NULL;
    }

//通过航班号查询航班
Airport* AirlineGraph::FindAirportByName(string name)
{
    for(int i=0;i<mAirportNumber;i++)
    {
        if(mAirportHeadArray[i]->mAirportName==name)
        {

          //  cout<<mAirportHeadArray[i]->mAirportName;
            return mAirportHeadArray[i];
        }
    }
    return NULL;
}

void AirlineGraph::InsertAirlineGraph(Airport* airport,Airline* airline)
//插入航班 创建时调用
{
    Airline* line=airport->mAdjAirline;
    if(line==NULL)
    {
        airport->mAdjAirline=airline;
    }else
    {
        //cout<<line->mAirlineName;
        while(line->mNextAirline!=NULL)
        {
            line=line->mNextAirline;
        }
        line->mNextAirline=airline;
    }
}
//展示航班
void AirlineGraph::ShowAirlineGraph()
{
    cout.setf(ios::left);
    cout<<endl;

    for(int i=0;i<mAirportNumber;i++)
    {
        cout<<endl;
      //  cout<<"======================================================================================================================";
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
      //  cout<<endl<<"【"<<airport->mLocation<<" - "<<airport->mAirportName<<"】"<<"\t"<<endl<<endl;
        while(airline!=NULL)
        {
         //   cout<<airline->mAirlineName<<"\t";
            /*cout<<setw(25)<<airline->mAirlineName<<setw(25);
            cout<<airline->mCompany<<setw(35);
            cout<<airline->mDepartureAirport<<setw(25);
            cout<<airline->mArrivalAirport<<setw(25);
            cout<<airline->mDepartureTime<<setw(13);
            cout<<airline->mArrivalTime<<setw(13);
            cout<<airline->mAirplaneModel<<setw(13);
            cout<<airline->mDepartureCity<<setw(13);
            cout<<airline->mArrivalCity;
            cout<<endl;*/
            airline=airline->mNextAirline;
        }
    }
   // cout<<endl<<"======================================================================================================================"<<endl;
}
//生成文件保存
Array AirlineGraph::GenerateAirlineJson()
{
    Array jsonArray;
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            Object jsonObj;
            jsonObj<<"公司"<<airline->mCompany;
            jsonObj<<"航班号"<<airline->mAirlineName;
            jsonObj<<"起始城市"<<airline->mDepartureCity;
            jsonObj<<"起飞机场"<<airline->mDepartureAirport;
            jsonObj<<"到达城市"<<airline->mArrivalCity;
            jsonObj<<"到达机场"<<airline->mArrivalAirport;
            jsonObj<<"起飞时间"<<airline->mDepartureTime;
            jsonObj<<"到达时间"<<airline->mArrivalTime;
            jsonObj<<"机型"<<airline->mAirplaneModel;
            jsonObj<<"价格"<<airline->mPrice;
            jsonObj<<"最大折扣"<<airline->mIntDiscount;
            jsonObj<<"满载"<<airline->mCapacity;
            jsonObj<<"当前人数"<<airline->mCurrentNumber;

            jsonArray<<jsonObj;
            //cout<<airline->mAirlineName<<"\t";
            /*cout<<setw(25)<<airline->mAirlineName<<setw(25);
            cout<<airline->mCompany<<setw(35);
            cout<<airline->mDepartureAirport<<setw(25);
            cout<<airline->mArrivalAirport<<setw(25);
            cout<<airline->mDepartureTime<<setw(13);
            cout<<airline->mArrivalTime<<setw(13);
            cout<<airline->mAirplaneModel<<setw(13);
            cout<<airline->mDepartureCity<<setw(13);
            cout<<airline->mArrivalCity;
            cout<<endl;*/
            airline=airline->mNextAirline;
        }
    }
    return jsonArray;
}

void AirlineGraph::WriteAirlineJson()
{
    ofstream outfile;
    outfile.open("Airline.json");
    Array jsonArray=GenerateAirlineJson();
    //cout<<jsonArray.json();
    outfile<<jsonArray.json();
    outfile.close();
}

int AirlineGraph::GetAirlineNumber()
{
    return mAirlineVector->size();
}

void AirlineGraph::InsertAirline(Airline* airline)
{
    Airport* dAirport=FindAirportByName(airline->mDepartureAirport);
    Airport* aAirport=FindAirportByName(airline->mArrivalAirport);

    if(dAirport==NULL||aAirport==NULL)
    {
        cout<<endl<<"机场不存在！";
        return;
    }else if(dAirport->mLocation!=airline->mDepartureCity||aAirport->mLocation!=airline->mArrivalCity)
    {
        cout<<endl<<"机场位置信息不匹配！";
        return;
    }else
    {
        mAirlineVector->push_back(airline);
        InsertAirlineGraph(dAirport,airline);    //插入到图
    }
}


string AirlineGraph::GetAirportLocation(string airportName)
{
    return FindAirportByName(airportName)->mLocation;
}
//起飞城市查询
Airline* AirlineGraph::FindAirlineByDepartureAirport(string name)
{
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mArrivalCity==name)
            {
                /*cout<<"航班号:"<<airline->mAirlineName<<endl;
                cout<<"公司:"<<airline->mCompany<<endl;
                cout<<"起始城市:"<<airline->mDepartureCity<<endl;
                cout<<"起飞机场:"<<airline->mDepartureAirport<<endl;
                cout<<"到达城市:"<<airline->mArrivalCity<<endl;
                cout<<"到达机场:"<<airline->mArrivalAirport<<endl;
                cout<<"起飞时间:"<<airline->mDepartureTime<<endl;
                cout<<"到达时间:"<<airline->mArrivalTime<<endl;
                cout<<"机型:"<<airline->mAirplaneModel<<endl;
                cout<<"价格:"<<airline->mPrice<<endl;
                cout<<"最大折扣:"<<airline->mIntDiscount<<endl;
                cout<<"满载:"<<airline->mCapacity<<endl;
                cout<<"当前人数:"<<airline->mCurrentNumber<<endl;*/

            }
            airline=airline->mNextAirline;
        }
    }
    return NULL;
}
//查询某个航线的情况如输入航班号
vector<Airline*>* AirlineGraph::FindAirlineByName(string name)
{
    vector<Airline*>* vec=new vector<Airline*>();
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mAirlineName==name)
            {
                /*cout<<"航班号:"<<airline->mAirlineName<<endl;
                cout<<"公司:"<<airline->mCompany<<endl;
                cout<<"起始城市:"<<airline->mDepartureCity<<endl;
                cout<<"起飞机场:"<<airline->mDepartureAirport<<endl;
                cout<<"到达城市:"<<airline->mArrivalCity<<endl;
                cout<<"到达机场:"<<airline->mArrivalAirport<<endl;
                cout<<"起飞时间:"<<airline->mDepartureTime<<endl;
                cout<<"到达时间:"<<airline->mArrivalTime<<endl;
                cout<<"机型:"<<airline->mAirplaneModel<<endl;
                cout<<"价格:"<<airline->mPrice<<endl;
                cout<<"最大折扣:"<<airline->mIntDiscount<<endl;
                cout<<"满载:"<<airline->mCapacity<<endl;
                cout<<"当前人数:"<<airline->mCurrentNumber<<endl;*/
                vec->push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    return vec;
}

void AirlineGraph::ShowAllAirlineToUser()
{
    cout.setf(ios::left);
    cout<<endl;

    for(int i=0;i<mAirportNumber;i++)
    {
        ShowAirlineByAirport(i);
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}


void AirlineGraph::ShowAirlineByAirport(int no)
{
    cout.setf(ios::left);
    cout<<endl;
    cout<<"========================================================================================================================================================================"<<endl;
    Airport* airport=mAirportHeadArray[no];
    Airline* airline=airport->mAdjAirline;
    cout<<endl<<"【"<<airport->mLocation<<" - "<<airport->mAirportName<<"】"<<"\t"<<endl<<endl;

    cout<<setw(10)<<"航班号";
    cout<<setw(25)<<"航空公司";
    cout<<setw(10)<<"出发地";
    cout<<setw(20)<<"起飞机场";
    cout<<setw(10)<<"目的地";
    cout<<setw(20)<<"着陆机场";
    cout<<setw(10)<<"起飞时间";
    cout<<setw(10)<<"抵达时间";
    cout<<setw(8)<<"机型";
    cout<<setw(8)<<"票价";
    cout<<setw(8)<<"折扣";
    cout<<setw(9)<<"折后票价";
    cout<<setw(8)<<"载客量";
    cout<<setw(8)<<"已售";
    cout<<setw(8)<<"余票";
    cout<<endl<<endl;

    while(airline!=NULL)
    {
        cout<<setw(10)<<airline->mAirlineName;
        cout<<setw(25)<<airline->mCompany;
        cout<<setw(10)<<airline->mDepartureCity;
        cout<<setw(20)<<airline->mDepartureAirport;
        cout<<setw(10)<<airline->mArrivalCity;
        cout<<setw(20)<<airline->mArrivalAirport;
        cout<<setw(10)<<airline->mDepartureTime;
        cout<<setw(10)<<airline->mArrivalTime;
        cout<<setw(8)<<airline->mAirplaneModel;
        cout<<setw(8)<<airline->mPrice;
        cout<<setw(8)<<airline->mIntDiscount/1000.0;
        cout<<setw(9)<<airline->mPrice*(1-airline->mIntDiscount/1000.0);
        cout<<setw(8)<<airline->mCapacity;
        cout<<setw(8)<<airline->mCurrentNumber;
        cout<<setw(8)<<airline->mCapacity-airline->mCurrentNumber;
        cout<<endl;
        airline=airline->mNextAirline;
    }
}

vector<int>* AirlineGraph::GetAirportIdByLocation(string loc)
{
    vector<int>* vec=new vector<int>();
    for(int i=0; i<mAirportNumber; i++)
    {
        if(mAirportHeadArray[i]->mLocation==loc)
        {
            vec->push_back(i);
        }
    }

    cout<<endl<<"========================================================================================================================================================================"<<endl;
return vec;
}

void AirlineGraph::ShowAirlineByCity(string city)
{
    vector<int>* vec=GetAirportIdByLocation(city);
    for(int i=0;i<vec->size();i++)
    {
        ShowAirlineByAirport((*vec)[i]);
    }
    if(vec->size()>0)
    {
        cout<<endl<<"========================================================================================================================================================================"<<endl;
    }else
    {
        cout<<endl<<"无航班信息！"<<endl;
    }
}
int AirlineGraph::timetransform(string t)
{
    if(t.length()==5)
        return (600*(t[0]-'0')+60*(t[1]-'0')+10*(t[3]-'0')+t[4]-'0');
    if(t.length()==4)
        return (60*(t[0]-'0')+6*(t[2]-'0')+(t[3]-'0'));
}
//按价格搜索
void AirlineGraph::SearchByPrice(int price1,int price2,string name1,string name2)
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mDepartureCity==name1&&airline->mArrivalCity==name2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=price1; i<price2; i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //用迭代器的方式输出容器对象的值
        {
            if((*m)->mPrice==i&&((*m)->flag==0))
            {
                cout<<"航班号:"<<(*m)->mAirlineName<<endl;
                cout<<"公司:"<<(*m)->mCompany<<endl;
                cout<<"起始城市:"<<(*m)->mDepartureCity<<endl;
                cout<<"起飞机场:"<<(*m)->mDepartureAirport<<endl;
                cout<<"到达城市:"<<(*m)->mArrivalCity<<endl;
                cout<<"到达机场:"<<(*m)->mArrivalAirport<<endl;
                cout<<"起飞时间:"<<(*m)->mDepartureTime<<endl;
                cout<<"到达时间:"<<(*m)->mArrivalTime<<endl;
                cout<<"机型:"<<(*m)->mAirplaneModel<<endl;
                cout<<"价格:"<<(*m)->mPrice<<endl;
                cout<<"最大折扣:"<<(*m)->mIntDiscount<<endl;
                cout<<"满载:"<<(*m)->mCapacity<<endl;
                cout<<"当前人数:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
    }
}
//按时间搜索
void AirlineGraph::SearchByTime(string time1,string time2,string name1,string name2)//按时间查找
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            airline->transformtime=timetransform(airline->mDepartureTime);
            if(airline->mDepartureCity==name1&&airline->mArrivalCity==name2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=timetransform(time1); i<timetransform(time2);i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //用迭代器的方式输出容器对象的值
        {
            if((*m)->transformtime==i&&((*m)->flag==0))
            {
                cout<<"航班号:"<<(*m)->mAirlineName<<endl;
                cout<<"公司:"<<(*m)->mCompany<<endl;
                cout<<"起始城市:"<<(*m)->mDepartureCity<<endl;
                cout<<"起飞机场:"<<(*m)->mDepartureAirport<<endl;
                cout<<"到达城市:"<<(*m)->mArrivalCity<<endl;
                cout<<"到达机场:"<<(*m)->mArrivalAirport<<endl;
                cout<<"起飞时间:"<<(*m)->mDepartureTime<<endl;
                cout<<"到达时间:"<<(*m)->mArrivalTime<<endl;
                cout<<"机型:"<<(*m)->mAirplaneModel<<endl;
                cout<<"价格:"<<(*m)->mPrice<<endl;
                cout<<"最大折扣:"<<(*m)->mIntDiscount<<endl;
                cout<<"满载:"<<(*m)->mCapacity<<endl;
                cout<<"当前人数:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
    }
}

//按时间排序
void AirlineGraph::SortByTime(string name1,string name2)
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            airline->transformtime=timetransform(airline->mDepartureTime);
            if(airline->mDepartureCity==name1&&airline->mArrivalCity==name2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=0; i<1440; i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //用迭代器的方式输出容器对象的值
        {
            if((*m)->transformtime==i&&((*m)->flag==0))
            {
                cout<<"航班号:"<<(*m)->mAirlineName<<endl;
                cout<<"公司:"<<(*m)->mCompany<<endl;
                cout<<"起始城市:"<<(*m)->mDepartureCity<<endl;
                cout<<"起飞机场:"<<(*m)->mDepartureAirport<<endl;
                cout<<"到达城市:"<<(*m)->mArrivalCity<<endl;
                cout<<"到达机场:"<<(*m)->mArrivalAirport<<endl;
                cout<<"起飞时间:"<<(*m)->mDepartureTime<<endl;
                cout<<"到达时间:"<<(*m)->mArrivalTime<<endl;
                cout<<"机型:"<<(*m)->mAirplaneModel<<endl;
                cout<<"价格:"<<(*m)->mPrice<<endl;
                cout<<"最大折扣:"<<(*m)->mIntDiscount<<endl;
                cout<<"满载:"<<(*m)->mCapacity<<endl;
                cout<<"当前人数:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
    }
}
void AirlineGraph::Search(string city1,string city2)
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mDepartureCity==city1&&airline->mArrivalCity==city2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=0; i<3030; i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //用迭代器的方式输出容器对象的值
        {
                cout<<"航班号:"<<(*m)->mAirlineName<<endl;
                cout<<"公司:"<<(*m)->mCompany<<endl;
                cout<<"起始城市:"<<(*m)->mDepartureCity<<endl;
                cout<<"起飞机场:"<<(*m)->mDepartureAirport<<endl;
                cout<<"到达城市:"<<(*m)->mArrivalCity<<endl;
                cout<<"到达机场:"<<(*m)->mArrivalAirport<<endl;
                cout<<"起飞时间:"<<(*m)->mDepartureTime<<endl;
                cout<<"到达时间:"<<(*m)->mArrivalTime<<endl;
                cout<<"机型:"<<(*m)->mAirplaneModel<<endl;
                cout<<"价格:"<<(*m)->mPrice<<endl;
                cout<<"最大折扣:"<<(*m)->mIntDiscount<<endl;
                cout<<"满载:"<<(*m)->mCapacity<<endl;
                cout<<"当前人数:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
}

void AirlineGraph::Book(Airline* airline)
{
    airline->mCurrentNumber=airline->mCurrentNumber+1;
    WriteAirlineJson();
}

void AirlineGraph::Unsubscribe(BookOrder* bookOrder)
{
    vector<Airline*>* vec=FindAirlineByName(bookOrder->mAirlineName);
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        if((*it)->mDepartureAirport==bookOrder->mDepartureAirport&&(*it)->mArrivalAirport==bookOrder->mArrivalAirport)
        {
            (*it)->mCurrentNumber=(*it)->mCurrentNumber-1;
            WriteAirlineJson();
            break;
        }
    }
    cout<<"==========================================="<<endl;
    cout<<endl;
    cout<<"================ 退票成功 ================="<<endl;
    cout<<endl;
    cout<<setw(12)<<"姓名:"<<bookOrder->mName<<endl;
    cout<<setw(12)<<"证件号:"<<bookOrder->mIdNumber<<endl;
    cout<<setw(12)<<"航班号:"<<bookOrder->mAirlineName<<endl;
    cout<<setw(12)<<"航空公司:"<<bookOrder->mCompany<<endl;
    cout<<setw(12)<<"出发地:"<<bookOrder->mDepartureCity<<endl;
    cout<<setw(12)<<"目的地:"<<bookOrder->mArrivalCity<<endl;
    cout<<setw(12)<<"购买价格:"<<bookOrder->mPrice<<endl;
    cout<<endl;
    cout<<"==========================================="<<endl;
}

//按价格排序
void AirlineGraph::SortByPrice(string name1,string name2)
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mDepartureCity==name1&&airline->mArrivalCity==name2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=0; i<3030; i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //用迭代器的方式输出容器对象的值
        {
            if((*m)->transformtime==i&&((*m)->flag==0))
            {
                cout<<"航班号:"<<(*m)->mAirlineName<<endl;
                cout<<"公司:"<<(*m)->mCompany<<endl;
                cout<<"起始城市:"<<(*m)->mDepartureCity<<endl;
                cout<<"起飞机场:"<<(*m)->mDepartureAirport<<endl;
                cout<<"到达城市:"<<(*m)->mArrivalCity<<endl;
                cout<<"到达机场:"<<(*m)->mArrivalAirport<<endl;
                cout<<"起飞时间:"<<(*m)->mDepartureTime<<endl;
                cout<<"到达时间:"<<(*m)->mArrivalTime<<endl;
                cout<<"机型:"<<(*m)->mAirplaneModel<<endl;
                cout<<"价格:"<<(*m)->mPrice<<endl;
                cout<<"最大折扣:"<<(*m)->mIntDiscount<<endl;
                cout<<"满载:"<<(*m)->mCapacity<<endl;
                cout<<"当前人数:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
    }
}
void AirlineGraph::Properline(string city1,string city2)
{
    //Search(city1,city2);
    Airport* airport=FindAirportByCity(city1);
    if(airport!=NULL)
    {
        Airline* airline = airport->mAdjAirline;
        while(airline!=NULL)
        {
            while(airline->mArrivalCity==city2)
            {
                /* cout<<"直达方案："<<endl;
                 cout<<setw(10)<<airline->mAirlineName;
                 cout<<setw(25)<<airline->mCompany;
                 cout<<setw(10)<<airline->mDepartureCity;
                 cout<<setw(20)<<airline->mDepartureAirport;
                 cout<<setw(10)<<airline->mArrivalCity;
                 cout<<setw(20)<<airline->mArrivalAirport;
                 cout<<setw(10)<<airline->mDepartureTime;
                 cout<<setw(10)<<airline->mArrivalTime;
                 cout<<setw(8)<<airline->mAirplaneModel;
                 cout<<setw(8)<<airline->mPrice;
                 cout<<setw(8)<<airline->mIntDiscount/1000.0;
                 cout<<setw(9)<<airline->mPrice*(1-airline->mIntDiscount/1000.0);
                 cout<<setw(8)<<airline->mCapacity;
                 cout<<setw(8)<<airline->mCurrentNumber;
                 cout<<setw(8)<<airline->mCapacity-airline->mCurrentNumber;
                 cout<<endl;*/
                airline=airline->mNextAirline;
            }
            string transfercity = airline->mArrivalCity;          //中转机场
            Airport* transfer = FindAirportByCity(transfercity);     //
            cout<<transfer;
            if(transfer!=NULL)
            {
                Airline* airlines = transfer->mAdjAirline;
                while(airlines!=NULL)
                {
                    if(airlines->mArrivalCity==city2&&((timetransform(airline->mArrivalTime))<(timetransform(airlines->mDepartureTime))))
                    {
                        cout<<"中转方案"<<endl;
                        cout<<setw(10)<<airline->mAirlineName;
                        cout<<setw(25)<<airline->mCompany;
                        cout<<setw(10)<<airline->mDepartureCity;
                        cout<<setw(20)<<airline->mDepartureAirport;
                        cout<<setw(10)<<airline->mArrivalCity;
                        cout<<setw(20)<<airline->mArrivalAirport;
                        cout<<setw(10)<<airline->mDepartureTime;
                        cout<<setw(10)<<airline->mArrivalTime;
                        cout<<setw(8)<<airline->mAirplaneModel;
                        cout<<setw(8)<<airline->mPrice;
                        cout<<setw(8)<<airline->mIntDiscount/1000.0;
                        cout<<setw(9)<<airline->mPrice*(1-airline->mIntDiscount/1000.0);
                        cout<<setw(8)<<airline->mCapacity;
                        cout<<setw(8)<<airline->mCurrentNumber;
                        cout<<setw(8)<<airline->mCapacity-airline->mCurrentNumber;
                        cout<<endl;
                        cout<<setw(10)<<airlines->mAirlineName;
                        cout<<setw(25)<<airlines->mCompany;
                        cout<<setw(10)<<airlines->mDepartureCity;
                        cout<<setw(20)<<airlines->mDepartureAirport;
                        cout<<setw(10)<<airlines->mArrivalCity;
                        cout<<setw(20)<<airlines->mArrivalAirport;
                        cout<<setw(10)<<airlines->mDepartureTime;
                        cout<<setw(10)<<airlines->mArrivalTime;
                        cout<<setw(8)<<airlines->mAirplaneModel;
                        cout<<setw(8)<<airlines->mPrice;
                        cout<<setw(8)<<airlines->mIntDiscount/1000.0;
                        cout<<setw(9)<<airlines->mPrice*(1-airline->mIntDiscount/1000.0);
                        cout<<setw(8)<<airlines->mCapacity;
                        cout<<setw(8)<<airlines->mCurrentNumber;
                        cout<<setw(8)<<airlines->mCapacity-airline->mCurrentNumber;
                        cout<<endl;
                    }
                    airlines = airlines->mNextAirline;
                }

            }
            airline=airline->mNextAirline;
        }
    }
}

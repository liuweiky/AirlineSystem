#include "AirlineGraph.h"

AirlineGraph::AirlineGraph()
{
    LoadAirport();
    LoadAirline();
  //  ShowAirlineGraph();
  //  WriteAirlineJson();
  //  char airline[10]="CZ6684";
  //  string name = airline;
  //  FindByAirlineName(name);
        char name1[10]="北京";
        char name2[10]="上海";
        string de = name1;
        string ar = name2;
        SortByPrize(de,ar);
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
    AirportArray.parse(s);
    mAirportNumber=AirportArray.size();
  //  cout<<mAirportNumber<<endl;
    mAirportHeadArray=new Airport*[mAirportNumber];
    for(int i=0;i<mAirportNumber;i++)
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
    AirlineArray.parse(s);
    mAirlineNumber=AirlineArray.size();
    cout<<mAirlineNumber;
    mAirlineArray=new Airline*[mAirlineNumber];
    for(int i=0;i<mAirlineNumber;i++)
    {
        mAirlineArray[i]=new Airline();
        mAirlineArray[i]->mAirlineName=AirlineArray.get<Object>(i).get<String>("航班号");
        mAirlineArray[i]->mCompany=AirlineArray.get<Object>(i).get<String>("公司");
        mAirlineArray[i]->mDepartureAirport=AirlineArray.get<Object>(i).get<String>("起飞机场");
        mAirlineArray[i]->mArrivalAirport=AirlineArray.get<Object>(i).get<String>("到达机场");
        mAirlineArray[i]->mDepartureTime=AirlineArray.get<Object>(i).get<String>("起飞时间");
        mAirlineArray[i]->mArrivalTime=AirlineArray.get<Object>(i).get<String>("到达时间");
        mAirlineArray[i]->mAirplaneModel=AirlineArray.get<Object>(i).get<String>("机型");
        mAirlineArray[i]->mDepartureCity=AirlineArray.get<Object>(i).get<String>("起始城市");
        mAirlineArray[i]->mArrivalCity=AirlineArray.get<Object>(i).get<String>("到达城市");
        mAirlineArray[i]->mPrice=AirlineArray.get<Object>(i).get<Number>("价格");
        mAirlineArray[i]->mIntDiscount=AirlineArray.get<Object>(i).get<Number>("最大折扣");
        mAirlineArray[i]->mCapacity=AirlineArray.get<Object>(i).get<Number>("满载");
        mAirlineArray[i]->mCurrentNumber=AirlineArray.get<Object>(i).get<Number>("当前人数");
        Airport* airport=FindAirportByName(mAirlineArray[i]->mDepartureAirport);
        //cout<<mAirlineArray[i]->mAirlineName<<endl;
        if(airport!=NULL)
        {
            //cout<<airport->mAirportName;
            InsertAirline(airport,mAirlineArray[i]);
        }
    }
    infile.close();
    //cout<<AirlineArray.json();
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
//插入航班 创建时调用
void AirlineGraph::InsertAirline(Airport* airport,Airline* airline)
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
        cout<<"======================================================================================================================";
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        cout<<endl<<"【"<<airport->mLocation<<" - "<<airport->mAirportName<<"】"<<"\t"<<endl<<endl;
        while(airline!=NULL)
        {
            cout<<airline->mAirlineName<<"\t";
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
    cout<<endl<<"======================================================================================================================"<<endl;
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
    cout<<jsonArray.json();
    outfile<<jsonArray.json();
}
//查询某个航线的情况如输入航班号
void AirlineGraph::FindByAirlineName(string name)
{
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mAirlineName==name)
            {
                cout<<"航班号:"<<airline->mAirlineName<<endl;
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
                cout<<"当前人数:"<<airline->mCurrentNumber<<endl;
            }
            airline=airline->mNextAirline;
        }
    }
}
//按价格排序
void AirlineGraph::SortByPrize(string name1,string name2)
{
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mDepartureCity==name1&&airline->mArrivalCity==name2)
            {
                cout<<"航班号:"<<airline->mAirlineName<<endl;
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
                cout<<"当前人数:"<<airline->mCurrentNumber<<endl;
            }
            airline=airline->mNextAirline;
        }
    }
}

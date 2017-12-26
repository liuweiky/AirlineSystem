#include "AirlineGraph.h"

AirlineGraph::AirlineGraph()
{
    LoadAirport();
    LoadAirline();
    ShowAirlineGraph();
    //WriteAirlineJson();
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

        Airport* airport=GetAirportByName(airline->mDepartureAirport);
        if(airport!=NULL)   //判断机场是否存在
        {
            InsertAirlineGraph(airport,airline);    //插入到图
        }
    }
    infile.close();
    //cout<<AirlineArray.json();
}
//通过航班号查询航班
Airport* AirlineGraph::GetAirportByName(string name)
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
void AirlineGraph::InsertAirlineGraph(Airport* airport,Airline* airline)
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
            airline=airline->mNextAirline;
        }
    }
    cout<<endl<<"======================================================================================================================"<<endl;
}
//生成json
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
    Airport* dAirport=GetAirportByName(airline->mDepartureAirport);
    Airport* aAirport=GetAirportByName(airline->mArrivalAirport);

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
        WriteAirlineJson(); //写出，更新航线数据文件
    }
}

string AirlineGraph::GetAirportLocation(string airportName)
{
    return GetAirportByName(airportName)->mLocation;
}

//输入航班号获取所有可能的航线
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
    vector<Airline*> vec;
    Airport* airport=mAirportHeadArray[no];
    Airline* airline=airport->mAdjAirline;
    while(airline!=NULL)
    {
        vec.push_back(airline);
        airline=airline->mNextAirline;
    }
    for(int i=1;i<vec.size();i++)  //插入排序
    {
        Airline* airline=vec[i];
        int j;
        for(j=i-1;j>=0&&(airline->GetAirlineDepartureTimeStamp())<vec[j]->GetAirlineDepartureTimeStamp();j--)
        {
            vec[j+1]=vec[j];
        }
        vec[j+1]=airline;
    }
    cout.setf(ios::left);
    cout<<endl;
    cout<<"========================================================================================================================================================================"<<endl;
    /*Airport* airport=mAirportHeadArray[no];
    Airline* airline=airport->mAdjAirline;*/
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

    for(vector<Airline*>::iterator it=vec.begin();it!=vec.end();it++)
    {
        Airline* airline=*it;
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
    }
}

vector<int>* AirlineGraph::GetAirportIdByLocation(string loc)
{
    vector<int>* vec=new vector<int>();
    for(int i=0;i<mAirportNumber;i++)
    {
        if(mAirportHeadArray[i]->mLocation==loc)
        {
            vec->push_back(i);
        }
    }
    return vec;
}

vector<Airline*>* AirlineGraph::GetAirlineByDACity(string departure,string arrival)
{
    vector<Airline*>* vec=new vector<Airline*>();
    vector<int>* dAirportVec=new vector<int>();
    dAirportVec=GetAirportIdByLocation(departure);
    for(vector<int>::iterator dit=dAirportVec->begin();dit!=dAirportVec->end();dit++)
    {
        Airline* airline=mAirportHeadArray[*dit]->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mArrivalCity==arrival)
            {
                vec->push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    return vec;
}

void AirlineGraph::ShowDACityAirlineByDiscountPrice(string departure,string arrival)
{
    vector<Airline*>* vec=GetAirlineByDACity(departure,arrival);

    for(int i=1;i<vec->size();i++)  //插入排序
    {
        Airline* airline=(*vec)[i];
        int j;
        for(j=i-1;j>=0&&(airline->GetPriceAfterDiscount())<(*vec)[j]->GetPriceAfterDiscount();j--)
        {
            (*vec)[j+1]=(*vec)[j];
        }
        (*vec)[j+1]=airline;
    }

    cout<<endl<<"========================================================================================================================================================================"<<endl;
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
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        Airline* airline=*it;
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
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}

void AirlineGraph::ShowDACityAirlineByDepartureTime(string departure,string arrival)
{
    vector<Airline*>* vec=GetAirlineByDACity(departure,arrival);

    for(int i=1;i<vec->size();i++)
    {
        Airline* airline=(*vec)[i];
        int j;
        for(j=i-1;j>=0&&(airline->GetAirlineDepartureTimeStamp())<(*vec)[j]->GetAirlineDepartureTimeStamp();j--)
        {
            (*vec)[j+1]=(*vec)[j];
        }
        (*vec)[j+1]=airline;
    }

    cout<<endl<<"========================================================================================================================================================================"<<endl;
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
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        Airline* airline=*it;
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
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;
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

void AirlineGraph::Book(Airline* airline)
{
    airline->mCurrentNumber=airline->mCurrentNumber+1;  //已订人数+1
    WriteAirlineJson(); //写出，更新本地数据
}

void AirlineGraph::Unsubscribe(BookOrder* bookOrder)
{
    vector<Airline*>* vec=FindAirlineByName(bookOrder->mAirlineName);
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        if((*it)->mDepartureAirport==bookOrder->mDepartureAirport&&(*it)->mArrivalAirport==bookOrder->mArrivalAirport)
        {
            (*it)->mCurrentNumber=(*it)->mCurrentNumber-1;  //已订人数-1
            WriteAirlineJson(); //写出，更新本地数据
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

void AirlineGraph::GetAdvisableRouteWithDFS(string departure,string arrival)
{
    int InD[mAirportNumber]={0};
    int visit[mAirportNumber]={0};
    for(int i=0;i<mAirportNumber;i++)
    {
        Airline* airline=mAirportHeadArray[i]->mAdjAirline;
        while(airline!=NULL)
        {
            InD[GetAirportByName(airline->mArrivalAirport)->No]+=1; //统计机场入度
            airline=airline->mNextAirline;
        }
    }


    //int d=GetAirportByName()
    //vector< vector<Airline*> >* mainVec=new vector< vector<Airline*> >();
    vector<Airline*> routeVec;
    vector<Route>* mainVec=new vector<Route>();
    //DFS(9,29,InD,visit,mainVec,routeVec);
    /*for(vector< vector<Airline*> >::iterator it=mainVec->begin();it!=mainVec->end();it++)
    {
        vector<Airline*> vec=*it;
        for(int i=0;i<vec.size();i++)
        {
            cout<<vec[i]->mAirlineName<<"->";
        }
        cout<<endl;
    }*/

    BFS(9,29,InD,visit,mainVec);
    cout<<mainVec->size();
    for(vector<Route>::iterator it=mainVec->begin();it!=mainVec->end();it++)
    {
        (*it).ShowRoute();
        cout<<endl;
    }
}

void AirlineGraph::BFS(int f,int a,int* InD,int* visit,vector<Route>* mainVec)
{
    int k=5;   //参数k
    queue<Route> q;
    Route r;
    r.mPrevNo=f;
    q.push(r);
    while(!q.empty())
    {
        Route r0=q.front();
        q.pop();
        Airline* airline=mAirportHeadArray[r0.mPrevNo]->mAdjAirline;
        while(airline!=NULL)
        {
            if(!r0.CheckPass(airline->mArrivalAirport))
            {
                if((r0.mAirlineVec.size()>0&&r0.mAirlineVec[r0.mAirlineVec.size()-1]->GetAirlineArrivalTimeStamp()<airline->GetAirlineDepartureTimeStamp())
                        ||r0.mAirlineVec.size()==0) //若不是始发航线，则需要判断前后航班时间是否赶得上
                {
                    int no=GetAirportByName(airline->mArrivalAirport)->No;
                    if(visit[no]<k*InD[no])    //入度的k倍，经过一个点是入度的10倍。决定BFS精密程度，但是运行时间会增大
                    {
                        Route rNew=r0;
                        rNew.mAirlineVec.push_back(airline);
                        rNew.mPrevNo=no;
                        visit[no]+=1;
                        if(no!=a)
                        {
                            q.push(rNew);
                        }
                        else
                        {
                            mainVec->push_back(rNew);
                        }
                    }
                }
            }
            airline=airline->mNextAirline;
        }
    }
}

void AirlineGraph::DFS(int v,int a,int* InD,int* visit,vector< vector<Airline*> >* mainVec,vector<Airline*> routeVec)
{
    if(v!=a)    //未到达目的地
    {

        /*for(int j=0;j<routeVec.size();j++)
        {
            cout<<routeVec[j]<<"  ";
        }
        cout<<endl;*/

        visit[v]+=1;
        //cout<<"visit: "<<visit[v]<<"ind: "<<InD[v]<<endl;
        Airline* airline=mAirportHeadArray[v]->mAdjAirline;
        //cout<<v<<endl;
        while(airline!=NULL)
        {
            //cout<<airline->mAirlineName<<endl;
            int no=GetAirportByName(airline->mArrivalAirport)->No;
            bool tag=0;
            for(int i=0;i<routeVec.size();i++)
            {
                if(routeVec[i]->mArrivalAirport==airline->mArrivalAirport)
                {
                    tag=1;
                    break;
                }
            }
            if(routeVec.size()==0)
            {
                if(visit[no]<InD[no]&&!tag)   //比较访问次数，检测是否小于入度
                {
                    vector<Airline*> newRoute;
                    for(vector<Airline*>::iterator it=routeVec.begin(); it!=routeVec.end(); it++)
                    {
                        newRoute.push_back(*it);
                    }
                    newRoute.push_back(airline);
                    DFS(no,a,InD,visit,mainVec,newRoute);
                }
                else
                {
                    //cout<<"大于入度"<<endl;
                }
            }
            else if(routeVec[routeVec.size()-1]->GetAirlineArrivalTimeStamp()<airline->GetAirlineDepartureTimeStamp()/*&&airline->GetAirlineDepartureTimeStamp()<airline->GetAirlineArrivalTimeStamp()*/)
            {
                if(visit[no]<InD[no]&&!tag)   //比较访问次数，检测是否小于入度
                {
                    vector<Airline*> newRoute;
                    for(vector<Airline*>::iterator it=routeVec.begin(); it!=routeVec.end(); it++)
                    {
                        newRoute.push_back(*it);
                    }
                    newRoute.push_back(airline);
                    DFS(no,a,InD,visit,mainVec,newRoute);
                }
                else
                {
                    //cout<<"大于入度"<<endl;
                }
            }
            airline=airline->mNextAirline;
        }
    }else   //到达目的地，终止DFS
    {
        visit[v]+=1;
        /*for(int i=0;i<routeVec.size();i++)
        {
            cout<<routeVec[i]->mArrivalAirport<<"->";
        }
        cout<<endl;*/
        mainVec->push_back(routeVec);   //将路径保存至 mainVec
        /*for(int j=0;j<routeVec.size();j++)
        {
            cout<<routeVec[j]<<"  ";
        }*/
        //cout<<endl;
    }

}

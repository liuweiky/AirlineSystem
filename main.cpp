#include <iostream>
#include <fstream>
#include "jsonxx.h"
#include "System.h"

using namespace std;
using namespace jsonxx;

int main()
{
    cout<<"ºÇºÇ"<<endl;
    cout << "Hello world!" << endl;
    string teststr(
        "{"
        "  \"foo\" : 1,"
        "  \"bar\" : false,"
        "  \"person\" : {\"name\" : \"GWB\", \"age\" : 60,},"
        "  \"data\": [\"abcd\", 42],"
        "}"
    );


    System* system=new System();
    //system->InsertAirlineInfo();
    //system->mAirlineGraph->ShowAirlineGraph();

    //system->ShowAllAirlineToUser();

    //system->ShowAllAirlineToUser();
    //system->ShowAirlineByAirport(0);
    //system->ShowAirlineByCity("±±¾©");
    //system->SearchAirline("CZ6394");
    system->Book();
    system->Unsubscribe();
    system->Book();

    Object obj;
    obj<<"Airline Number"<<999;
    Array arr;
    //a << Object("key", "value");
    Object AirlineObj1;
    AirlineObj1<<"From"<<"Beijing";
    AirlineObj1<<"To"<<"Shanghai";
    AirlineObj1<<"Cost"<<1200;

    Object AirlineObj2;
    AirlineObj2<<"From"<<"Changchun";
    AirlineObj2<<"To"<<"Shanghai";
    AirlineObj2<<"Cost"<<780;
    arr<<AirlineObj1;
    arr<<AirlineObj2;
    obj<<"Airlines"<<arr;

    //cout<<obj.get<Array>("Airlines").size();



    Array a;
    a << 123;
    a << "hello world";
    a << 3.1415;
    a << 99.95f;
    a << 'h';
    a << Object("key", "value");
    Object o;
    o << "key1" << "value";
    o << "key2" << 123;
    o << "key3" << a;
    //cout <<obj.json()<< endl;
    cout <<o.json()<< endl;

    Object oo;
    oo.parse(teststr);
    //cout << oo.json() << endl;
    return 0;
}

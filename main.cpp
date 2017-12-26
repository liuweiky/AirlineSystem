#include <iostream>
#include <fstream>
#include "jsonxx.h"
#include "System.h"

using namespace std;
using namespace jsonxx;

int main()
{
    cout << "Hello world!" << endl;
    System* system=new System();
    //system->InsertAirlineInfo();
    //system->mAirlineGraph->ShowAirlineGraph();
    //system->ShowAllAirlineToUser();
    //system->ShowAirlineByAirport(0);
    //system->ShowAirlineByCity("北京");
    //system->SearchAirline("CZ6394");
    //system->Book();
    //system->Unsubscribe();
    //system->Book();
    //system->mAirlineGraph->ShowDACityAirlineByDiscountPrice("长春","上海");

    //system->mAirlineGraph->ShowDACityAirlineByDepartureTime("北京","深圳");

    //system->mAirlineGraph->GetAdvisableRouteWithDFS("长春","上海");

    return 0;
}

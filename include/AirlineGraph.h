#ifndef AIRLINEGRAPH_H
#define AIRLINEGRAPH_H
#include "Airport.h"
#include "Airline.h"
#include "jsonxx.h"
#include <fstream>
#include <iomanip>
#include <vector>

using std::setw;
using namespace jsonxx;

class AirlineGraph
{
    public:
        AirlineGraph();
        virtual ~AirlineGraph();
        int mAirportNumber; //机场数量
        Airport** mAirportHeadArray;
        vector<Airline*>* mAirlineVector;
        Airport* FindAirportByName(string name);
        int GetAirlineNumber();
        void InsertAirlineGraph(Airport* airport,Airline* airline);
        void ShowAirlineGraph();
        void WriteAirlineJson();
    protected:

    private:
        Array GenerateAirlineJson();
        void LoadAirport();
        void LoadAirline();
};

#endif // AIRLINEGRAPH_H

#ifndef AIRLINEGRAPH_H
#define AIRLINEGRAPH_H
#include "Airport.h"
#include "Airline.h"
#include "jsonxx.h"
#include <fstream>
#include <iomanip>

using std::setw;
using namespace jsonxx;

class AirlineGraph
{
    public:
        AirlineGraph();
        virtual ~AirlineGraph();
        int mAirportNumber;
        int mAirlineNumber;
        Airport** mAirportHeadArray;
        Airline** mAirlineArray;
        Airport* FindAirportByName(string name);
        void InsertAirline(Airport* airport,Airline* airline);
        void ShowAirlineGraph();

    protected:

    private:
        void GenerateAirport();
        void LoadAirport();
        void LoadAirline();
};

#endif // AIRLINEGRAPH_H

#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"

class System
{
    public:
        System();
        virtual ~System();
        AirlineGraph* mAirlineGraph;
        void InsertAirlineInfo();
        void ShowAllAirlineToUser();
    protected:

    private:
};

#endif // SYSTEM_H

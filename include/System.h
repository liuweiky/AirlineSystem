#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"

class System
{
    public:
        System();
        virtual ~System();
        AirlineGraph* mAirlineGraph;
    protected:

    private:
};

#endif // SYSTEM_H

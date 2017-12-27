#ifndef TIMEUTIL_H
#define TIMEUTIL_H
#include <string>
#include <stdlib.h>

using namespace std;

class TimeUtil
{
    public:
        TimeUtil();
        virtual ~TimeUtil();
        static int GetTimeStamp(string time);
    protected:

    private:
};

#endif // TIMEUTIL_H

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
        static int GetTimeStamp(string time);   //string×ªÊ±¼ä´Á
    protected:

    private:
};

#endif // TIMEUTIL_H

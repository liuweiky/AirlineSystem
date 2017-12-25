#ifndef BOOK_H
#define BOOK_H
#include "Airport.h"
#include "Airline.h"

class book
{
    public:
        string name;
        string id;
        string mAirlineName;
        string mCompany;
        string mDepartureAirport;
        string mArrivalAirport;
        string mDepartureTime;
        string mArrivalTime;
        string mAirplaneModel;
        string mDepartureCity;
        string mArrivalCity;
        int ticket_num;
        int leftticket_num;
        book();
        virtual ~book();
        book(int leftticket_num);
    protected:

    private:
};

#endif // BOOK_H

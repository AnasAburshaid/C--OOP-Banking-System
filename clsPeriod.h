#pragma once
#include "clsDate.h"

class clsPeriod
{
public:

    clsDate StartDate;
    clsDate EndDate;

    clsPeriod(clsDate StartDate, clsDate DateTo)
    {
        this->StartDate = StartDate;
        this->EndDate = EndDate;

    }

    static bool IsPeriodOverLap(clsPeriod Period1, clsPeriod Period2)
    {
        return (!(clsDate::IsDateBeforeDate2(Period2.EndDate, Period1.StartDate) ||clsDate::IsDateAfterDate2(Period2.StartDate, Period1.EndDate)));
    }



    bool IsOverLapWith(clsPeriod Period2)
    {
        return IsPeriodOverLap(*this, Period2);
    }

    void Print()
    {
        cout << "Period Start: ";
        StartDate.Print();


        cout << "Period End: ";
        EndDate.Print();


    }

};

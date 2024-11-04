#pragma warning(disable : 4996)
#pragma once

#include<iostream>
#include<string>
#include"clsString.h"

using namespace std;

class clsDate
{
private:

    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;

public:

    clsDate()
    {
        time_t t = time(0);//get time now
        tm* now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
    }

    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DaysInOrderYear, short Year)
    {
        //this will construct a date by date order in year
        clsDate Date1 = GetDateFromDayOrderInYear(DaysInOrderYear, Year);
        _Day = Date1.Day;
        _Month = Date1.Month;
        _Year = Date1.Year;
    }

    clsDate(string sDate)
    {
        vector<string> vDate;
        vDate = clsString::Split(sDate, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    void SetDay(short Day)
    {
        _Day = Day;
    }

    short GetDay()
    {
        return _Day;
    }

    __declspec(property(get = GetDay, put = SetDay)) short  Day;

    void SetMonth(short Month)
    {
        _Month = Month;
    }

    short GetMonth()
    {
        return _Month;
    }

    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    void SetYear(short Year)
    {
        _Year = Year;
    }

    short GetYear()
    {
        return _Year;
    }

    __declspec(property(get = GetYear, put = SetYear)) short Year;

    void Print()
    {
        cout << DateToString() << endl;
    }

    static clsDate GetSystemDate()
    {
        //System Date
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;

        return clsDate(Day, Month, Year);
    }

    static string GetSystemDateTimeString()
    {
        //System Date And Time String
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(Year) + "/" + to_string(Month) + "/" + to_string(Day) 
            + " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
    }


    static bool IsValidDate(clsDate Date)
    {
        return !((Date.Day < 1 || Date.Day > NumberOfDaysInAMonth(Date.Month, Date.Year)) || (Date.Month < 1 || Date.Month > 12));
    } 

    bool IsValid()
    {
        return IsValidDate(*this);
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
    }

    string DateToString()
    {
        return DateToString(*this);
    }

    static bool IsLeapYear(short Year)
    {
        // if year is divisible by 4 and is not divisible by 100
        // Or if year is divisible by 400 
        // then it is a leap year 
        return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
    }

    bool IsLeapYear()
    {
        return IsLeapYear(_Year);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return IsLeapYear(Year) ? 365 : 364;
    }

    short NumberOfDaysInAYear()
    {
        return NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(_Year);
    }

    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;

        short NumberOfDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        return ((Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1]);
        // if you reach here then its 30 days
        // return 30;
    }

    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(_Month, _Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return NumberOfMinutesInAMonth(_Month, _Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(_Month, _Year);
    }


    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;

        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;
        // Gregorian
        // 0:Sun, 1:Mon, 2:Tue...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    static short DayOfWeekOrder(clsDate Date)
    {
        return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    }

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat" };
        return arrDayNames[DayOfWeekOrder];
    }

    static string DayShortName(short Day, short Month, short Year)
    {
        string arrDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat" };
        return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
    }

    static string DayShortName(clsDate Date)
    {
        return DayShortName(Date.Day, Date.Month, Date.Year);
    }

    string DayShortName()
    {
        return DayShortName(DayOfWeekOrder());
    }

    static string MonthShortName(short MonthNumber)
    {
        string arrMonths[12] = { "Jan", "Feb", "Mar",
                                 "Apr", "May", "Jun",
                                 "Jul", "Aug", "Sep",
                                 "Oct", "Nev", "Dec" };
        return arrMonths[MonthNumber - 1];
    }

    string MonthShortName()
    {
        return MonthShortName(_Month);
    }

    static void PrintMonthCalendar(short Month, short Year)
    {
        short NumberOfDays;

        // Index of the day from 0 to 6
        short current = DayOfWeekOrder(1, Month, Year);

        NumberOfDays = NumberOfDaysInAMonth(Month, Year);

        // Print the Current month name
        printf("\n  ______________%s________________\n",
            MonthShortName(Month).c_str());

        // Print the columns
        printf("\n  Sun  Mon  Tue  Wed  Thr  Fri  Sat\n");

        // Print appropriate spaces
        short i;
        for (i = 0; i < current; i++)
            printf("     ");

        for (short j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);

            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }

        printf("\n  _________________________________\n");
    }

    void PrintMonthCalendar()
    {
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(short Year)
    {
        printf("\n  _________________________________\n");
        printf("\n         Calendar - %d", Year);
        printf("\n  _________________________________\n");

        for (short i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }

        return;
    }

    void PrintYearCalendar()
    {
        PrintYearCalendar(_Year);
    }

    static short NumberOfDaysFromBegainingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;
        for (short i = 1; i <= Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, Year);
        }

        TotalDays += Day;

        return TotalDays;
    }

    static short NumberOfDaysFromBegainingOfTheYear(clsDate Date)
    {
        return NumberOfDaysFromBegainingOfTheYear(Date.Day, Date.Month, Date.Year);
    }

    short NumberOfDaysFromBegainingOfTheYear()
    {
        return NumberOfDaysFromBegainingOfTheYear(_Day, _Month, _Year);
    }

    static clsDate GetDateFromDayOrderInYear(short DaysOrderInYear, short Year)
    {
        clsDate Date;
        short RemainingDays = DaysOrderInYear;
        short MonthDays = 0;

        Date.Year = Year;
        Date.Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainingDays;
                break;
            }
        }

        return Date;
    }

    void AddDays(short DaysToAdd)
    {
        short RemainingDays = DaysToAdd + NumberOfDaysFromBegainingOfTheYear(_Day, _Month, _Year);
        short MonthDays = 0;

        _Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(_Month, _Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                _Month++;

                if (_Month > 12)
                {
                    _Month = 1;
                    _Year++;
                }
            }
            else
            {
                _Day = RemainingDays;
                break;
            }

        }


    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {

        return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);

    }

    bool IsDateBeforeDate2(clsDate Date2)
    {
        //note: *this sends the current object :-).
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        //return (Date1.Year == Date2.Year ? (Date1.Month == Date2.Month ? (Date1.Day == Date2.Day ? true : false)  : false) : false);
        return ((Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day));
    }

    bool IsDateEqualDate2(clsDate Date2)
    {
        //note: *this sends the current object :-).
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2)) && (!IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDateAfterDate2(clsDate Date2)
    {
        //note: *this sends the current object :-).
        return IsDate1AfterDate2(*this, Date2);
    }

    enum enDatesCompare { Before = -1, Eqaul = 0, After = 1 };

    static enDatesCompare CompareDates(clsDate Date1, clsDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enDatesCompare::Before;

        if (IsDate1EqualDate2(Date1, Date2))
            return enDatesCompare::Eqaul;

        /*if (IsDate1AfterDate2(Date1, Date2))
            return enDatesCompare::After;*/

            // This is faster
        return enDatesCompare::After;
    }

    enDatesCompare CompareDates(clsDate Date2)
    {
        return CompareDates(*this, Date2);
    }


    static bool IsLastDayInTheMonth(clsDate Date1)
    {
        return (Date1.Day == NumberOfDaysInAMonth(Date1.Month, Date1.Year));
    }

    bool IsLastDayInTheMonth()
    {
        return IsLastDayInTheMonth(*this);
    }

    static bool IsLastMonthInTheYear(short Month)
    {
        return (Month == 12);
    }

    static clsDate AddOneDay(clsDate& Date)
    {
        if (IsLastDayInTheMonth(Date))
        {
            if (IsLastMonthInTheYear(Date.Month))
            {
                Date.Month = 1;
                Date.Day = 1;
                Date.Year++;
            }
            else
            {
                Date.Day = 1;
                Date.Month++;
            }

        }
        else
        {
            Date.Day++;
        }

        return Date;
    }

    void AddOneDay()
    {
        //*this = AddOneDay(*this);
        AddOneDay(*this);
    }

    static void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        clsDate TempDate;

        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short SwapFlagValue = 1;

        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            //Swap Dates
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))// Or use Function IsDate1LessThanDate2() The Same 
        {
            Date1 = AddOneDay(Date1);
            Days++;
        }

        return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;

    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static short CalculateMyAgeInDays(clsDate DateOfBirth)
    {
        return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
    }

    //
    static clsDate IncreaseDateByXDays(short DaysToAdd, clsDate& Date)
    {

        for (short i = 1; i <= DaysToAdd; i++)
        {
            Date = AddOneDay(Date);
        }

        return Date;
    }

    void IncreaseDateByXDays(short DaysToAdd)
    {
        IncreaseDateByXDays(DaysToAdd, *this);
    }

    static clsDate IncreaseDateByOneWeek(clsDate& Date)
    {
        for (short i = 1; i <= 7; i++)
        {
            Date = AddOneDay(Date);
        }

        return Date;
    }

    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }

        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        IncreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate IncreaseDateByOneMonth(clsDate& Date)
    {
        if (Date.Month == 12)
        {
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Month++;
        }

        //last check day in date should not exceed max days in the current month
        //example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
        // be 28/2/2022
        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    void IncreaseDateByOneMonth()
    {
        IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
    {

        for (short i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void IncreaseDateByXMonths(short Months)
    {
        IncreaseDateByXMonths(Months, *this);
    }

    static clsDate IncreaseDateByOneYear(clsDate& Date)
    {
        Date.Year++;
        return Date;
    }

    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }

    static clsDate IncreaseDateByXYears(short Years, clsDate& Date)
    {

        for (short i = 1; i <= Years; i++)
        {
            Date = IncreaseDateByOneYear(Date);
        }

        return Date;
    }

    void IncreaseDateByXYears(short Years)
    {
        IncreaseDateByXYears(Years, *this);
    }

    static clsDate IncreaseDateByXYearsFaster(short Years, clsDate& Date)
    {

        Date.Year += Years;
        return Date;

    }

    void IncreaseDateByXYearsFaster(short Years)
    {
        IncreaseDateByXYearsFaster(Years, *this);
    }

    static clsDate IncreaseDateByOneDecade(clsDate& Date)
    {
        //Period of 10 years
        Date.Year += 10;
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecades(short Decades, clsDate& Date)
    {

        for (short i = 1; i <= Decades; i++)
        {
            Date = IncreaseDateByOneDecade(Date);
        }
        // Or 
        //Date.Year = (Decades * 10);

        return Date;
    }

    void IncreaseDateByXDecades(short Decades)
    {
        IncreaseDateByXDecades(Decades, *this);
    }

    static clsDate IncreaseDateByXDecadesFaster(short Decades, clsDate& Date)
    {

        Date.Year += (Decades * 10);
        return Date;

    }

    void IncreaseDateByXDecadesFaster(short Decades)
    {
        IncreaseDateByXDecadesFaster(Decades, *this);
    }

    static clsDate IncreaseDateByOneCentury(clsDate& Date)
    {
        //Period of 100 years
        Date.Year += 100;
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }

    static clsDate IncreaseDateByOneMillennium(clsDate& Date)
    {
        //Period of 1000 years
        Date.Year += 1000;
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }
    //

    //
    static clsDate DecreaseDateByOneDay(clsDate& Date)
    {
        if (Date.Day == 1)
        {
            if (Date.Month == 1)
            {
                Date.Month = 12;
                Date.Day = 31;
                Date.Year--;
            }
            else
            {
                Date.Month--;
                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            }

        }
        else
        {
            Date.Day--;
        }

        return Date;
    }

    void DecreaseDateByOneDay()
    {
        DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
    {

        for (short i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

    void DecreaseDateByXDays(short Days)
    {
        DecreaseDateByXDays(Days, *this);
    }

    static clsDate DecreaseDateByOneWeek(clsDate& Date)
    {
        for (short i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

    void DecreaseDateByOneWeek()
    {
        DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }

        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        DecreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate DecreaseDateByOneMonth(clsDate& Date)
    {
        if (Date.Month == 1)
        {
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Month--;
        }

        //last check day in date should not exceed max days in the current month
        //example if date is 31/3/2022 Dereasing one month should not be 31/2/2022, it should
        // be 28/2/2022
        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
    {

        for (short i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void DecreaseDateByXMonths(short Months)
    {
        DecreaseDateByXMonths(Months, *this);
    }

    static clsDate DecreaseDateByOneYear(clsDate& Date)
    {
        Date.Year--;
        return Date;
    }

    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
    {

        for (short i = 1; i <= Years; i++)
        {
            Date = DecreaseDateByOneYear(Date);
        }

        return Date;
    }

    void DecreaseDateByXYears(short Years)
    {
        DecreaseDateByXYears(Years, *this);
    }

    static clsDate DecreaseDateByXYearsFaster(short Years, clsDate& Date)
    {

        Date.Year -= Years;
        return Date;

    }

    void DecreaseDateByXYearsFaster(short Years)
    {
        DecreaseDateByXYearsFaster(Years, *this);
    }

    static clsDate DecreaseDateByOneDecade(clsDate& Date)
    {
        //Period of -10 years
        Date.Year -= 10;
        return Date;
    }

    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
    {

        for (short i = 1; i <= Decades; i++)
        {
            Date = DecreaseDateByOneDecade(Date);
        }
        // Or 
        //Date.Year -= (Decades * 10);

        return Date;
    }

    void DecreaseDateByXDecades(short Decades)
    {
        DecreaseDateByXDecades(Decades, *this);
    }

    static clsDate DecreaseDateByXDecadesFaster(short Decades, clsDate& Date)
    {

        Date.Year -= Decades * 10;
        return Date;

    }

    void DecreaseDateByXDecadesFaster(short Decades)
    {
        DecreaseDateByXDecadesFaster(Decades, *this);
    }

    static clsDate DecreaseDateByOneCentury(clsDate& Date)
    {
        //Period of -100 years
        Date.Year -= 100;
        return Date;
    }

    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate& Date)
    {
        //Period of -1000 years
        Date.Year -= 1000;
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(*this);
    }

    static bool IsEndOfWeek(clsDate Date)
    {
        return DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;// 6 Is Satrday
    }

    bool IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date)
    {
        // weekends are Fri and Sat
        short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekEnd()
    {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date)
    {
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay()
    {
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOFWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    }

    short DaysUntilTheEndOFWeek()
    {
        return DaysUntilTheEndOFWeek(*this);
    }

    static short DaysUntilTheEndOFMonth(clsDate Date)
    {
        clsDate EndOfMonthDate;
        EndOfMonthDate.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
        EndOfMonthDate.Month = Date.Month;
        EndOfMonthDate.Year = Date.Year;

        return GetDifferenceInDays(Date, EndOfMonthDate, true);
    }

    short DaysUntilTheEndOFMonth()
    {
        return DaysUntilTheEndOFMonth(*this);
    }

    static short DaysUntilTheEndOFYear(clsDate Date)
    {
        clsDate EndOfYearDate;
        EndOfYearDate.Day = 31;
        EndOfYearDate.Month = 12;
        EndOfYearDate.Year = Date.Year;

        return GetDifferenceInDays(Date, EndOfYearDate, true);
    }

    short DaysUntilTheEndOFYear()
    {
        return DaysUntilTheEndOFYear(*this);
    }

    static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
    {
        short DaysCount = 0;
        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                DaysCount++;

            DateFrom = AddOneDay(DateFrom);
        }

        return DaysCount;
    }

    static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
    {

        return CalculateBusinessDays(DateFrom, DateTo);

    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
    {
        short WeekEndCounter = 0;

        while ((VacationDays + WeekEndCounter) != 0)
        {
            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;

            DateFrom = AddOneDay(DateFrom);
            VacationDays--;
        }

        while (IsWeekEnd(DateFrom))
        {
            DateFrom = AddOneDay(DateFrom);
        }

        return DateFrom;//End Date Vacation
    }

    static string FormattingDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
    {
        string FormattedDateString = "";
        FormattedDateString = clsString::ReplaceWord(DateFormat, "dd", to_string(Date.Day));
        FormattedDateString = clsString::ReplaceWord(FormattedDateString, "mm", to_string(Date.Month));
        FormattedDateString = clsString::ReplaceWord(FormattedDateString, "yyyy", to_string(Date.Year));

        return FormattedDateString;
    }

    string FormattingDate(string DateFormat = "dd/mm/yyyy")
    {
        return FormattingDate(*this, DateFormat);
    }

};
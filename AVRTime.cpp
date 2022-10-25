#include "AVRTime.h"
#include "Arduino.h"

bool am;
bool update;
int currentSec;
int pastSec;
int Second;
int Minute;
int Hour;
int hour12;
int Day;
int Month;
int Year1; // The left two digits of the year
int Year2; // The right two digits of the year
int uploadTime = 10;
String STRTime;
String STRDate;
String monthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

AVRTime::AVRTime(const char *_date, const char *_time)
{
    STRTime = String(_time);
    STRDate = String(_date);
}

void AVRTime::begin() // Set date and time
{
    String h, m, s, d, mo, y1, y2;

    // PARSE DATA //
    h = String(STRTime[0]) + String(STRTime[1]);
    m = String(STRTime[3]) + String(STRTime[4]);
    s = String(STRTime[6]) + String(STRTime[7]);
    d = String(STRDate[4]) + String(STRDate[5]);
    mo = String(STRDate[0]) + String(STRDate[1]) + String(STRDate[2]);
    y1 = String(STRDate[7]) + String(STRDate[8]);
    y2 = String(STRDate[9]) + String(STRDate[10]);
    ////////////////

    Second = (s.toInt() + uploadTime); // Account for upload time
    Minute = m.toInt();
    Hour = h.toInt();
    if (Hour < 12)
    {
        am = true;
        hour12 = Hour;
    }
    else
    {
        am = false;
        hour12 = Hour - 12;
    }
    if (hour12 == 0)
    {
        hour12 = 12;
    }
    for (int i = 0; i < 12; i++)
    {
        if (m == monthName[i])
        {
            Month = i + 1;
        }
    }
    Day = d.toInt();
    Year1 = y1.toInt();
    Year2 = y2.toInt();
}

void AVRTime::setTime(int h, int m, int s)
{
    Second = s;
    Minute = m;
    Hour = h;
    if (Hour < 12)
    {
        am = true;
        hour12 = Hour;
    }
    else
    {
        am = false;
        hour12 = Hour - 12;
    }
    if (hour12 == 0)
    {
        hour12 = 12;
    }
}

void AVRTime::setStringTime(String h, String m, String s)
{
    Second = (s.toInt() + 9);
    Minute = m.toInt();
    Hour = h.toInt();
    if (Hour < 12)
    {
        am = true;
        hour12 = Hour;
    }
    else
    {
        am = false;
        hour12 = Hour - 12;
    }
    if (hour12 == 0)
    {
        hour12 = 12;
    }
}

void AVRTime::setDate(int d, int m, int y)
{
    Day = d;
    Month = m;
    Year1 = y / 100;
    Year2 = y - (Year1 * 100);
}

void AVRTime::setStringDate(String d, String m, String y)
{
    for (int i = 0; i < 12; i++)
    {
        if (m == monthName[i])
        {
            Month = i + 1;
        }
    }
    Day = d.toInt();
    Year1 = String(y[0] + y[1]).toInt();
    Year2 = String(y[2] + y[3]).toInt();
}

void AVRTime::keepTime()
{
    currentSec = (millis() / 1000);
    if (currentSec != pastSec)
    {
        update = true;
        Second++;
        if (Second > 59)
        {
            Second = 0;
            Minute++;
        }
        if (Minute > 59)
        {
            Minute = 0;
            Hour++;
        }
        if (Hour > 23)
        {
            Hour = 0;
            Day++;
        }
        switch (Month)
        {
        case 1: // January
            if (Day > 31)
            {
                Day = 1;
                Month++;
            }
            break;
        case 2: // February
            if ((Year2 % 4) == 0)
            { // Account for the leap year
                if (Day > 29)
                {
                    Day = 1;
                    Month++;
                }
            }
            else
            {
                if (Day > 28)
                {
                    Day = 1;
                    Month++;
                }
            }
            break;
        case 3: // March
            if (Day > 31)
            {
                Day = 1;
                Month++;
            }
            break;
        case 4: // April
            if (Day > 30)
            {
                Day = 1;
                Month++;
            }
            break;
        case 5: // May
            if (Day > 31)
            {
                Day = 1;
                Month++;
            }
            break;
        case 6: // June
            if (Day > 30)
            {
                Day = 1;
                Month++;
            }
            break;
        case 7: // July
            if (Day > 31)
            {
                Day = 1;
                Month++;
            }
            break;
        case 8: // August
            if (Day > 31)
            {
                Day = 1;
                Month++;
            }
            break;
        case 9: // September
            if (Day > 30)
            {
                Day = 1;
                Month++;
            }
            break;
        case 10: // October
            if (Day > 31)
            {
                Day = 1;
                Month++;
            }
            break;
        case 11: // November
            if (Day > 30)
            {
                Day = 1;
                Month++;
            }
            break;
        case 12: // December
            if (Day > 31)
            {
                Day = 1;
                Month = 1;
                Year2++;
                if (Year2 > 99)
                {
                    Year1++;
                    Year2 = 0;
                }
            }
            break;
        }
        pastSec = currentSec;
    }
}

void AVRTime::printFormattedTime(Print *aSerial)
{
    aSerial->print("The time is: ");
    aSerial->print(hour12);
    aSerial->print(':');
    aSerial->print((Minute < 10) ? ("0" + String(Minute)) : Minute);
    aSerial->print(am ? "AM" : "PM");
    aSerial->print(" and ");
    aSerial->print((Second < 10) ? ("0" + String(Second)) : Second);
    aSerial->println(" Seconds.");
    aSerial->print("The date is: ");
    aSerial->print(Month);
    aSerial->print('/');
    aSerial->print(Day);
    aSerial->print('/');
    aSerial->print(Year1);
    aSerial->println(Year2);
}

bool AVRTime::validTime(int startH, int startM, int endH, int endM)
{ //!!!IN 24 HOUR FORMAT!!!
    if (startH >= endH)
        endH += 23;
    if (Hour > startH)
    {
        if (Hour == endH)
        {
            if (Minute <= endM)
                return true;
            else
                return false;
        }
        else
        {
            if (Hour < endH)
                return true;
            else
                return false;
        }
    }
    else
    {
        if (Hour == startH)
        {
            if (Minute >= startM)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

bool AVRTime::validGivenTime(int Ghour, int Gmin, int startH, int startM, int endH, int endM)
{
    if (startH >= endH)
        endH += 23;
    if (Ghour >= startH && Gmin >= startM)
    {
        if (Ghour <= endH && Gmin <= endM)
        {
            return true;
        }
    }
    return false;
}

bool AVRTime::timeUpdate()
{
    if (update)
    {
        update = false;
        return true;
    }
    return false;
}
int AVRTime::getSecond()
{
    return Second;
}
int AVRTime::getMinute()
{
    return Minute;
}
int AVRTime::getHour(bool hour12Time)
{
    if (hour12Time)
        return hour12;
    else
        return Hour;
}
int AVRTime::getDate()
{
    return Day;
}
int AVRTime::getMonth()
{
    return Month;
}
int AVRTime::getYear()
{
    return (Year1 * 100) + Year2;
}
String AVRTime::parseHour()
{
    return String(STRTime[0]) + String(STRTime[1]);
}
String AVRTime::parseMin()
{
    return String(STRTime[3]) + String(STRTime[4]);
}
String AVRTime::parseSec()
{
    return String(STRTime[6]) + String(STRTime[7]);
}
String AVRTime::parseDay()
{
    return String(STRDate[4]) + String(STRDate[5]);
}
String AVRTime::parseMonth()
{
    return String(STRDate[0]) + String(STRDate[1]) + String(STRDate[2]);
}
String AVRTime::parseYear()
{
    return String(STRDate[7]) + String(STRDate[8]) + String(STRDate[9]) + String(STRDate[10]);
}

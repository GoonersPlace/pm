#include "TimeSlot.h"
#include <iostream>

using namespace std;

TimeSlot::TimeSlot()
{
    day = "";
    slotNumber = 0;
    startTime = "";
    endTime = "";
}

TimeSlot::TimeSlot(string day, int slotNumber,
                   string startTime, string endTime)
{
    this->day = day;
    this->slotNumber = slotNumber;
    this->startTime = startTime;
    this->endTime = endTime;
}

void TimeSlot::Display()
{
    cout << day << " - Slot " << slotNumber
         << " - " << startTime
         << " -> " << endTime << endl;
}

string TimeSlot::getDay()
{
    return day;
}

int TimeSlot::getSlotNumber()
{
    return slotNumber;
}

string TimeSlot::getStartTime()
{
    return startTime;
}

string TimeSlot::getEndTime()
{
    return endTime;
}

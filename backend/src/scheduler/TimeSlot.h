#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <string>
using namespace std;

class TimeSlot
{
private:
    string day;
    int slotNumber;
    string startTime;
    string endTime;

public:
    TimeSlot();

    TimeSlot(string day, int slotNumber,
             string startTime, string endTime);

    void Display();

    string getDay();
    int getSlotNumber();
    string getStartTime();
    string getEndTime();
};
int InputTimeSlots(TimeSlot slots[], int maxSlots);

#endif

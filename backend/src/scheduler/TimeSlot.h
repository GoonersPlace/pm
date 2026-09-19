#ifndef TIMESLOT_H
#define TIMESLOT_H

#define MAX_TIMESLOT 100

struct TimeSlot
{
    char day[10];
    int slotNumber;
    char startTime[10];
    char endTime[10];
};

void InputTimeSlots(TimeSlot slots[], int &n);
void OutputTimeSlots(TimeSlot slots[], int n);

#endif

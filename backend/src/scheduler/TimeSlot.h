#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <string>
using namespace std;
class TimeSlot {
public:
    int id;
    string day;
    string startTime;
    string endTime;
    TimeSlot();
    TimeSlot(int id, string day, string startTime, string endTime);
    void display();
};

#endif

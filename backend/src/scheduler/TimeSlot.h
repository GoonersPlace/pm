#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <string>
using namespace std;

class TimeSlot
{
private:
    string day;        // Thứ trong tuần
    int slotNumber;    // Số thứ tự tiết
    string startTime;  // Giờ bắt đầu
    string endTime;    // Giờ kết thúc

public:
    TimeSlot();

    TimeSlot(string day, int slotNumber,
             string startTime, string endTime);

    string getDay();
    int getSlotNumber();
    string getStartTime();
    string getEndTime();
};

#endif

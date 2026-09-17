#include "TimeSlot.h"
#include <iostream>

TimeSlot::TimeSlot() {
    id = 0;
    day = "";
    startTime = "";
    endTime = "";
}

TimeSlot::TimeSlot(int id, string day, string startTime, string endTime) {
    this->id = id;
    this->day = day;
    this->startTime = startTime;
    this->endTime = endTime;
}

